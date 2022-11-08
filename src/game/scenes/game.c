#include "../hud/hud.h"
#include "../player/player.c"

void pauseGame()
{
    ImGuiIO* io = igGetIO();
    cvAddText(io->DisplaySize.x/50 / 2 - 0.5, -(io->DisplaySize.y / 50 / 2) + 0.5, CV_COL32_WHITE, "PAUSE");
}

void displayGame(App* app)
{
    drawHUDScore(app);
}

void processingGame(App* app)
{
    playerScript();
    if (igIsKeyDown(ImGuiKey_Space))
    {
        pauseGame();
    }
    if (igIsKeyDown(ImGuiKey_A))
    {
        app->scene = 3;
    }
}