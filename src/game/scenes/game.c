#include "../hud/hud.h"
#include "../player/player.h"
#include "../bullet.h"
#include "../../mine/mine.h"
#include "../hud/hud.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>

int level = 1;

void gameInit(App* app)
{
	if (app->gameinit == false)
	{
		mineInit();
		for (int i = 0; i < MAX_BULLET_COUNT; i++)
			bulletInit(&app->bullets[i]);
		playerInit(app, &app->player[0], 0);
		playerInit(app, &app->player[1], 1);
		app->gameinit = true;
	}
}

void pauseGame(App* app)
{
	if (igIsKeyPressed(ImGuiKey_Space, 0))
		app->paused = !app->paused;

	if (app->paused == true)
	{
		ImGuiIO* io = igGetIO();
		cvAddText(io->DisplaySize.x/50 / 2 - 0.5, -(io->DisplaySize.y / 50 / 2) + 0.5, CV_COL32_WHITE, "PAUSE");

		if (igIsKeyPressed(ImGuiKey_Escape, 0))
		{
			app->gameinit = false;
			app->paused = false;
			app->twoPlayers = false;
			app->scene = 0;
			chanceMineFloating = 100;
			chanceMineFireball = 0;
			chanceMineMagnetic = -20;
			chanceMineFiremag  = -40;
			level = 0;
		}
	}
}


void displayGame(App* app)
{
	if (!app->gameinit)
		return;
    drawHUDScore(&app->player[0], false);
    drawHUDLivesLeft(&app->player[0], false);
	if (app->twoPlayers)
	{
		drawHUDLivesLeft(&app->player[1], true);
		drawHUDScore(&app->player[1], true);
	}
    drawHUDLevel(app);
}

void processingGame(App* app)
{
	if (!app->gameinit)
		return;
    if (!app->paused)
    {
        playerScript(&app->player[0]);
        entityMineUpdate(app, app->player);
        if (igIsKeyPressed(ImGuiKey_C, 0))
        {
            app->graphics.show_collisionbox = !app->graphics.show_collisionbox;
        }
    }
    pauseGame(app);
	Player *players[2];
	players[0] = &app->player[0];
	players[1] = &app->player[1];

	Player **ptr = players;
	bulletUpdate(app, ptr, 2);
}