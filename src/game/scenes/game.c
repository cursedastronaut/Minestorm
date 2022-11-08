#include "../hud/hud.h"

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
            app->HUD.p1_lives = 0;
            app->HUD.p2_lives = 0;
            app->HUD.p1_score = 0;
            app->HUD.p2_score = 0;
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
    pauseGame(app);
    if (app->paused == false)
    {

        //DEBUG
        if (igIsKeyDown(ImGuiKey_A))
        {
            app->scene = 3;
        }
    }
    
}