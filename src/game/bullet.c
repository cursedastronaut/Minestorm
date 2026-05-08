#include "bullet.h"
#include "../app.h"
#include <canvas.h>

void bulletUpdate(App* app, Player **player, uint8_t playerAmount)
{
	ImGuiIO* io = igGetIO();
	for (int i = 0; i < MAX_BULLET_COUNT; i++)
	{
		if (gBullets[i].isActive == true)
		{
			gBullets[i].pos.x += gBullets[i].momentum.x;  //cosf(gBullets[i].angle + (PI / 2)) * app -> deltaTime * 50; //Moves the bullet according
			gBullets[i].pos.y += gBullets[i].momentum.y;  //sinf(gBullets[i].angle + (PI / 2)) * app -> deltaTime * 50; //to its firing angle.
			gBullets[i].timeBeforeDeath -= app->deltaTime;    //Lowering its lifetime.
			cvAddPoint(gBullets[i].pos.x, gBullets[i].pos.y, CV_COL32(255,255,255,gBullets[i].opacity)); //Drawing the bullet

			if (gBullets[i].timeBeforeDeath <= 1.0) //Gradually lowering the opacity
			{                                       //of the bullet before it dies.
				gBullets[i].opacity -= 255/60;
			}

			if (gBullets[i].timeBeforeDeath <= 0)
			{
				gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME;
				gBullets[i].isActive = false;                       //Killing the bullet.
			}
			float2 bulletSquare[4] =
			{
				{ -0.2f + gBullets[i].pos.x, 0.2f + gBullets[i].pos.y},
				{ 0.2f + gBullets[i].pos.x, 0.2f + gBullets[i].pos.y},
				{ 0.2f + gBullets[i].pos.x, -0.2f + gBullets[i].pos.y},
				{ -0.2f + gBullets[i].pos.x, -0.2f + gBullets[i].pos.y}
			};
			
			for (int j = 0; j < playerAmount; ++j)
			{
				float2 playerSquare[4] =
				{
					{ -0.5f + player[j]->pos.x, 0.5f + player[j]->pos.y},
					{ 0.5f + player[j]->pos.x, 0.5f + player[j]->pos.y},
					{ 0.5f + player[j]->pos.x, -0.5f + player[j]->pos.y},
					{ -0.5f + player[j]->pos.x, -0.5f + player[j]->pos.y}
				};
				if (checkCollisionSquareSquare(bulletSquare, playerSquare, app) && player[j]->invincibility <= 0)
				{
					gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME;
					gBullets[i].isActive = 0;                       //Killing the bullet.
					--player[j]->lives;
					player[j]->invincibility = 5.0f;
				}
			}
			

			//Making it loop with the borders
			if (gBullets[i].pos.x > io->DisplaySize.x / 50 + 1)
				gBullets[i].pos.x = -0.5;
			if (gBullets[i].pos.x < -1)
				gBullets[i].pos.x = io->DisplaySize.x / 50 + 0.5;

			if (gBullets[i].pos.y < -io->DisplaySize.y / 50 - 2 )
				gBullets[i].pos.y = 0.5;
			if (gBullets[i].pos.y > 1)
				gBullets[i].pos.y = -io->DisplaySize.y / 50 - 0.5;
		}
	}
}