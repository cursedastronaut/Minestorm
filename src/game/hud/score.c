#pragma once
#include <string.h>
#include "../player/player.c"

void addScore(int score, int player)
{
    gPlayers[player].score += score;
}

//Draws the score on the HUD.
void drawHUDScore(App* app)
{
    for (int i = 0; i !=2; i++)
    {
        char output[15]; //Max score can only contain 8 numbers. (99999999)
        sprintf(output, "Score: %d", gPlayers[i].score);
        ImGuiIO* io = igGetIO();
        if (i == 0)
        {
        cvAddText(
             8/50,
            0, CV_COL32_WHITE, output);
        }
        else
        {
            if (app->twoPlayers)
                cvAddText((io->DisplaySize.x/50) - (strlen(output)) * 0.4,0, CV_COL32_WHITE, output);
        }
    }
}