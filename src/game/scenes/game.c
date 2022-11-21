#include "../hud/hud.h"
//#include "../player/player.c"
#include "../entities/floating_mine.c"

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
    if (igIsKeyReleased(ImGuiKey_Space))
    {
        app->paused = !app->paused;
    }

    if (app->paused == true)
    {
        ImGuiIO* io = igGetIO();
        cvAddText(io->DisplaySize.x/50 / 2 - 0.5, -(io->DisplaySize.y / 50 / 2) + 0.5, CV_COL32_WHITE, "PAUSE");

        if (igIsKeyReleased(ImGuiKey_Escape))
        {
            app->paused = false;
            app->twoPlayers = false;
            app->scene = 0;
        }


    }
    
}

void displayGame(App* app)
{
    drawHUDScore(app);
    drawHUDLivesLeft(app);
}

void processingGame(App* app)
{
    if (app->paused != true)
    {
        playerScript(app);
        entityMineFloating(app);
        entityType();
        if (igIsKeyReleased(ImGuiKey_C))
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