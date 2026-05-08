#include "player.h"
#include "../bullet.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <toolbox.h>
#include "../../app.h"

//Initializes the player's position
void playerInit(App* app, Player* player, bool playerNumber)
{
	player->app = app;

	player->app->deltaTime += 0;
	//Sets the positions
	player->pos = (float2){.x =12, 5.f - 7.f};
	if (playerNumber == 1)
		player->pos = (float2){.x = 7.5f, .y = -7.f};
	player->score = 0; //Initial score
	player->lives = 3;
	player->momentumX = 0;
	player->momentumY = 0;
	player->angle = 0;
	player->invincibility = 5.0f;
	player->color = CV_COL32(255,0,0,255);
	if (playerNumber == 1)
		player->color = CV_COL32(0,255,0,255);
	if (playerNumber == 0)
	{
		player->controls.fire =				ImGuiKey_F;
		player->controls.forward =			ImGuiKey_R;
		player->controls.forwardAlt =		ImGuiKey_UpArrow;
		player->controls.rotateLeft =		ImGuiKey_D;
		player->controls.rotateLeftAlt =	ImGuiKey_LeftArrow;
		player->controls.rotateRight =		ImGuiKey_G;
		player->controls.rotateRightAlt =	ImGuiKey_RightArrow;
		player->controls.teleport =			ImGuiKey_T;
		player->controls.teleportAlt =		ImGuiKey_E;
	} else {
		player->controls.fire =				ImGuiKey_O;
		player->controls.forward =			ImGuiKey_Keypad8;
		player->controls.forwardAlt =		ImGuiKey_I;
		player->controls.rotateLeft =		ImGuiKey_Keypad4;
		player->controls.rotateLeftAlt =	ImGuiKey_J;
		player->controls.rotateRight =		ImGuiKey_Keypad6;
		player->controls.rotateRightAlt =	ImGuiKey_L;
		player->controls.teleport =			ImGuiKey_K;
		player->controls.teleportAlt =		ImGuiKey_Keypad9;
	}
}
//Draws the player to the screen
bool drawPlayer(Player *player)
{
	if (player->invincibility > 0)
	{
		cvAddTexture(player->pos.x, player->pos.y,  player->app->graphics.textures.forcefield);
		if (player->app->animtime % 6 == 0) //flickering effect
			return (true);
	}
	for (int i = 0; i < 6; ++i) // Looping through the points making the shape.
	{
		float2 newPoint = shapePlayer[i];
		float2 temp = newPoint;
		float2 xy = {0, 0};
		newPoint.x = rotatePoint(temp, xy, player->angle).x + player->pos.x;
		newPoint.y = rotatePoint(temp, xy, player->angle).y + player->pos.y;

		cvPathLineTo(newPoint.x, newPoint.y);
	}
	cvPathStroke(CV_COL32_WHITE, true);
	cvAddPoint(player->pos.x, player->pos.y, player->color);
}

//Teleports the player
void playerTeleport(Player	*player)
{
	ImGuiIO* io = igGetIO();
	player->invincibility = 2.0f;
	player->pos.x = rand() % ((int) io->DisplaySize.x / 50);
	player->pos.y = -rand() % ((int) io->DisplaySize.y / 50);
}

void killPlayer(Player *player)
{
	ma_engine_play_sound(&player->app->engine, "assets/audio/death.mp3", NULL);
	player->invincibility = 5.0;
	--player->lives;
}

void playerInvincibility(Player *player)
{
	if (player->invincibility > 0.0f)
	{
		player->invincibility -= player->app->deltaTime;
	}
}


void playerGameOver(Player *player)
{
	if (player->app->twoPlayers == true)
	{
		if (player->app->player[0].lives <= 0 && player->app->player[1].lives <= 0)
		{
			FILE* save2 = fopen("save2.sav", "r");
			if (save2)
			{
				fread(&player->app->bestScoreMultiplayer, sizeof(int), 2, save2);
				fclose(save2);
			}
			else
				player->app->bestScoreMultiplayer[0] = 0;
				player->app->bestScoreMultiplayer[0] = 1;
			for (int i = 0; i < 2; i++)
			{
				if (player->app->player[i].score > player->app->bestScoreMultiplayer[i])
				{
					player->app->bestScoreMultiplayer[i] = player->app->player[i].score;
					FILE* save2 = fopen("save2.sav", "w");
					if (save2)
					{
						fwrite(&player->app->bestScoreMultiplayer, sizeof(int), 2, save2);
						fclose(save2);
					}
				}
			}
			player->app->scene = 3;
			ma_engine_play_sound(&player->app->engine, "assets/audio/game_over.mp3", NULL);
		}
		for (int i = 0; i < 2; i ++)
			if (player->app->player[i].lives == 0)
			{
				player->app->player[i].pos.x = -5; 
				player->app->player[i].pos.y = -5;
			}
	}
	else
	{
		if (player->app->player[0].lives <= 0)
		{
			

			FILE* save1 = fopen("save1.sav", "r");
			if (save1)
			{
				fread(&player->app->bestScoreSingleplayer, sizeof(int), 1, save1);
				fclose(save1);
			}
			else
				player->app->bestScoreSingleplayer = 0;
			if (player->app->player[0].score > player->app->bestScoreSingleplayer)
			{
				player->app->bestScoreSingleplayer = player->app->player[0].score;
				FILE* save1 = fopen("save1.sav", "w");
				if (save1)
				{
					fwrite(&player->app->bestScoreSingleplayer, sizeof(int), 1, save1);
					fclose(save1);
				}
			}
			player->app->scene = 3;
			ma_engine_play_sound(&player->app->engine, "assets/audio/game-over.mp3", NULL);
		}
	} 
}

//Checks for input and prepare for movement
void playerControls(Player *player)
{
	if (player->lives == 0)
		return;
	if ((igIsKeyDown(player->controls.rotateLeft) || igIsKeyDown(player->controls.rotateLeftAlt)))
		player->angle += (480.0f * PI / 360.0f) * player->app->deltaTime;
	if (igIsKeyDown(player->controls.rotateRight) || igIsKeyDown(player->controls.rotateRightAlt))
		player->angle -= (480.0f * PI / 360.0f) * player->app->deltaTime;
	if (igIsKeyDown(player->controls.forward) || igIsKeyDown(player->controls.forwardAlt))
	{   
		player->momentumX += (sin(-player->angle) * 0.25f);
		player->momentumY += (cos(-player->angle) * 0.25f);
	}

	if (igIsKeyPressed(player->controls.teleport, 0) || igIsKeyPressed(player->controls.teleportAlt, 0))
		playerTeleport(player);
	if (igIsKeyPressed(player->controls.fire, 0))
	{
		bulletCreate(player);
		ma_engine_play_sound(&player->app->engine, "assets/audio/shooting.mp3", NULL);
	}
	if (player->angle > 2.0f * PI)
		player->angle = 0.0f;
	else if (player->angle < 0.0f)
		player->angle = 2.0f * PI;
}

//Actual movement processing
void playerMovement(Player *player)
{
	player->pos.x += player->momentumX * player->app->deltaTime;
	player->pos.y += player->momentumY * player->app->deltaTime;
	//Apply friction
	player->momentumX *= 0.98f;
	player->momentumY *= 0.98f;
}

//Checks if player is Out Of Bounds and moves him to the other side if yes
void playerOOB(Player *player)
{
	ImGuiIO* io = igGetIO();
	if (player->lives != 0)
	{
		if (player->pos.x > io->DisplaySize.x / 50 + 1)
			player->pos.x = -0.5;
		if (player->pos.x < -1)
			player->pos.x = io->DisplaySize.x / 50 + 0.5;

		if (player->pos.y < -io->DisplaySize.y / 50 - 2 )
			player->pos.y = 0.5;
		if (player->pos.y > 1)
			player->pos.y = -io->DisplaySize.y / 50 - 0.5;
	}
}
//Displays debug informations
void playerDebug(Player *player)
{
	igText("Player %p", player);
	igText("   X: %f", player->pos.x);
	igText("   Y: %f", player->pos.y);
	igText("   Momentum X: %f", player->momentumX);
	igText("   Momentum Y: %f", player->momentumY);
	igText("   Speed: %f", sqrtf(powf(player->momentumX, 2.0f) + powf(player->momentumY, 2.0f)));
	igText("   Angle: %f", player->angle);
	igText("   Inv.Time : %f", player->invincibility);
	igText("----------");
}
//Unites all of the above functions
void playerScript(Player *player)
{
	drawPlayer(player);
	playerControls(player);
	playerMovement(player);
	playerOOB(player);
	playerInvincibility(player);
	playerGameOver(player);
	playerDebug(player);
}
