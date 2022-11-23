#include "../hud/hud.h"
//#include "../player/player.c"
#include "../entities/mine.c"

void gameInit(App* app)
{
    if (app->gameinit == false)
    {
        mineInit(app);
        app->gameinit = true;
    }
}

void pauseGame(App* app)
{
    if (igIsKeyPressed(ImGuiKey_Space, 0))
    {
        app->paused = !app->paused;
    }

    if (app->paused == true)
    {
        ImGuiIO* io = igGetIO();
        cvAddText(io->DisplaySize.x/50 / 2 - 0.5, -(io->DisplaySize.y / 50 / 2) + 0.5, CV_COL32_WHITE, "PAUSE");

        if (igIsKeyPressed(ImGuiKey_Escape, 0))
        {
            playerInit(app);
            app->paused = false;
            app->twoPlayers = false;
            app->scene = 0;
            app->gameinit = false;
        }
    }
}


void displayGame(App* app)
{
    drawHUDScore(app);
    drawHUDLivesLeft(app);
    drawHUDLevel(app);
}

void processingGame(App* app)
{
    if (app->paused != true)
    {
        playerScript(app);
        entityMineUpdate(app);
        entityType();
        if (igIsKeyPressed(ImGuiKey_C, 0))
        {
            app->graphics.show_collisionbox = !app->graphics.show_collisionbox;
        }
    }
    pauseGame(app);
    /*
    if (igIsKeyDown(ImGuiKey_A))
    {
        app->scene = 3;
    }*/
}