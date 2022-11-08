#include "../hud/hud.h"

void pauseGame()
{
    
}

void displayGame(App* app)
{
    drawHUDScore(app);
}

void processingGame(App* app)
{
    if (igIsKeyDown(ImGuiKey_Space))
    {
        pauseGame();
    }
}