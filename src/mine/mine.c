#include "mine.h"
#include <stdlib.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <math.h>
#include <toolbox.h>
#include "../game/tinkering.h"
#include "../game/game.h"
#include "../game/player/player.h"
#include "../game/bullet.h"
#include "../app.h"

int chanceMineFloating = 100;
int chanceMineFireball = 0;
int chanceMineMagnetic = -20;
int chanceMineFiremag  = -40;

static int mineGeneration()
{
	int	temp = rand() % 100;
	if (temp > chanceMineFloating - 100 && temp <= chanceMineFloating)
		return MT_MineFloating;
	else if (temp > chanceMineFireball - 20 && temp <= chanceMineFireball)
		return MT_MineFire;
	else if (temp > chanceMineMagnetic - 20 && temp <= chanceMineMagnetic)
		return MT_MineMagnetic;
	else if (temp > chanceMineFiremag - 20 && temp <= chanceMineFiremag)
		return MT_MineFiremag;
}

void mineInit(Mine *mine)
{
	ImGuiIO* io = igGetIO();
	mine->angle = (rand() % 360) * (PI/180);
	mine->size = 3;
	mine->type = mineGeneration();

	//Sets a random position on the X axis (within the window's limits)
	mine->pos.x = rand() % ((int)igGetIO()->DisplaySize.x / 50);
	mine->pos.y = -rand() % ((int)igGetIO()->DisplaySize.y / 50);

	//Sets the momentum variables so that it goes in the direction of its angle.
	mine->momentum.x = cosf(mine->angle) * 0.1;
	mine->momentum.y = sinf(mine->angle) * 0.1;

	mine->isActive = true;
}

void spawnFireball(Mine *mine, Player *player)
{
	Mine *mines = player->app->mines;
	if (mine->type == MT_MineFire || mine->type == MT_MineFiremag)
	{
		for (size_t i = 0; i < MINE_MAX; i++)
		{
			if (mines[i].isActive == false)
			{
				float2 temp;
				float	normalizer;
				mines[i].angle = mine->angle;
				mines[i].size = 1;
				mines[i].type = MT_MineFireball;
				mines[i].pos = mine->pos;
				temp.x = player->pos.x - mines[i].pos.x;
				temp.y = player->pos.y - mines[i].pos.y;
				normalizer = sqrtf(powf(temp.x, 2.0f) + powf(temp.y, 2.0f));
				mines[i].momentum.x = temp.x / normalizer;
				mines[i].momentum.y = temp.y / normalizer;
				mines[i].isActive = true;
				break;
			}
		}
	}
}

void	spawnMine(Mine *mines, int size, float angle, float2 pos, mineType type)
{
	for (uint16_t i = 0; i < MINE_MAX; ++i)
	{
		if (mines[i].isActive == false)
		{
			mines[i].angle = angle;
			mines[i].size = size;
			mines[i].type = type;
			mines[i].pos.x = pos.x - 0.3;
			mines[i].pos.y = pos.y - 0.3;
			mines[i].momentum.x = cosf(mines[i].angle) * 0.1; //Sets the momentum variables so that it goes
			mines[i].momentum.y = sinf(mines[i].angle) * 0.1; //in the direction of its angle.
			mines[i].isActive = true;
			break;
		}
	}
}

void killMineFloating(Mine *mine, Player *player)
{
	//si la mine est petite ou si c'est une boule de feu, la détruire
	spawnFireball(mine, player);
	if (mine->size == 1)
		mine->isActive = false;
	//sinon, reduit la taille de la mine et en fait apparaitre une autre
	else
	{
		--mine->size;
		spawnMine(player->app->mines, mine->size, mine->angle, mine->pos, mine->type);
		// si la mine est de type fireball ou magnetic-fireball, faire apparaitre une fireball
	}
	mine->angle += PI;
	mine->momentum.x = cosf(mine->angle) * 0.1;
	mine->momentum.y = sinf(mine->angle) * 0.1;
}

void	drawMine(Mine *currentMine)
{
	int verticeAmount = 8;
	if (!currentMine->isActive)
		return;
	for (int j = 0; j < verticeAmount; ++j)     //Looping through the points
	{
		float2 newPoint;
		switch (currentMine->type)
		{
			case 0: newPoint = pointsFloat[j];
			verticeAmount = 6;
			break;
			case 1: newPoint = pointsFire[j];
			break;
			case 2: newPoint = pointsMagnetic[j];
			break;
			case 3: newPoint = pointsFiremag[j];
			break;
			case 4: newPoint = pointsFireball[j];
			break;
		}
		newPoint.x *= currentMine->size;
		newPoint.y *= currentMine->size;
		newPoint.x += currentMine->pos.x;
		newPoint.y += currentMine->pos.y;

		cvPathLineTo(newPoint.x, newPoint.y); 
	}
	cvPathStroke(CV_COL32_WHITE, 1);
}

bool checkMinesIntegrity(Mine *mines)
{
	bool	allMinesDead = true;
	for (int i = 0; i < MINE_MAX && allMinesDead; ++i)
		allMinesDead = !mines[i].isActive;
	if (!allMinesDead)
		return false;
	++level;
	if (level < 6)
	{
		chanceMineFloating += 20;
		chanceMineFireball += 20;
		chanceMineMagnetic += 20;
		chanceMineFiremag  += 20;
	}
	
	for (u_int16_t i = 0; i < MINE_AMOUNT_INITIAL; ++i)
		mineInit(&mines[i]);
	return true;
}

static void mineOOB(Mine *mine)
{
	//Loop around borders
	ImGuiIO* io = igGetIO();
	if (mine->pos.x > io->DisplaySize.x / 50 + 1)
		mine->pos.x = -0.5;
	if (mine->pos.x < -1)
		mine->pos.x = io->DisplaySize.x / 50 + 0.5;

	if (mine->pos.y < -io->DisplaySize.y / 50 - 2 )
		mine->pos.y = 0.5;
	if (mine->pos.y > 1)
		mine->pos.y = -io->DisplaySize.y / 50 - 0.5;
}

static void mineMovement(Mine *mine, App* app, Player *player)
{
	switch (mine->type)
	{
		case MT_MineFloating:
		case MT_MineFire:
			mine->pos.x += mine->momentum.x * app -> deltaTime * (4 - mine->size) * 3;
			mine->pos.y += mine->momentum.y * app -> deltaTime * (4 - mine->size) * 3;
			break;
		
		case MT_MineMagnetic:
		case MT_MineFiremag:
			float tempX;
			float tempY;
			float normalizer;
			tempX = player->pos.x - mine->pos.x;
			tempY = player->pos.y - mine->pos.y;
			normalizer = sqrtf(powf(tempX, 2.0f) + powf(tempY, 2.0f));
			mine->momentum.x = tempX / normalizer;
			mine->momentum.y = tempY / normalizer;
			mine->pos.x += mine->momentum.x * app -> deltaTime * (4 - mine->size) * 0.98;
			mine->pos.y += mine->momentum.y * app -> deltaTime * (4 - mine->size) * 0.98;
			break;

		case MT_MineFireball: //Fireball
			mine->pos.x += mine->momentum.x * app -> deltaTime * (4 - mine->size);
			mine->pos.y += mine->momentum.y * app -> deltaTime * (4 - mine->size);
			break;

		default:
			break;
	}
	mineOOB(mine);
}

void mineCollision(Mine *mine, App* app, Player *player)
{
	float2 mineBox[4] = 
	{
		{ mine->pos.x + (0.3f * mine->size), mine->pos.y + (0.3f * mine->size) },
		{ mine->pos.x + (0.3f * mine->size), mine->pos.y + (-0.3f * mine->size) },
		{ mine->pos.x + (-0.3f * mine->size), mine->pos.y + (-0.3f * mine->size) },
		{ mine->pos.x + (-0.3f * mine->size), mine->pos.y + (0.3f * mine->size) }
	};
	if (player->invincibility <= 0)
	{
		float2 collisionSquare[4] =
		{
			{ -0.5f + player->pos.x, 0.5f + player->pos.y},
			{ 0.5f + player->pos.x, 0.5f + player->pos.y},
			{ 0.5f + player->pos.x, -0.5f + player->pos.y},
			{ -0.5f + player->pos.x, -0.5f + player->pos.y}
		};
		if (checkCollisionSquareSquare(mineBox, collisionSquare, app->graphics.show_collisionbox))
			killPlayer(player);
	}
	
	//BULLET COLLISION
	for (int b = 0; b < MAX_BULLET_COUNT; ++b)
		bulletMineCollision(&player->app->bullets[b], mine, player->app, mineBox);
}

bool	mineUpdate(Mine *mine, App *app, Player *player)
{
	if (!mine->isActive)
		return false;
	mineMovement(mine, app, player);
	mineCollision(mine, app, player);
	#ifdef _DEBUG
	if (igIsKeyPressed(ImGuiKey_M, 0))
		for (int i = 0; i < MINE_MAX; ++i)
			mine->isActive = false;
	#endif
	return checkMinesIntegrity(app->mines);
}
