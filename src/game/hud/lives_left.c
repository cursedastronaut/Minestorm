#pragma once
#include "../player/player.c"

void drawHUDLivesLeft(App* app)
{
    cvAddFormattedText(0,-1, CV_COL32_WHITE, "P1 Li%s: %d", gPlayers[0].lives > 1 ? "ves" : "fe",gPlayers[0].lives);
    if (app->twoPlayers)
    {
        char output[15];
        sprintf(output, "P2 Li%s: %d", gPlayers[1].lives > 1 ? "ves" : "fe",gPlayers[1].lives);
        cvAddFormattedText(( igGetIO()->DisplaySize.x/50 ) - (strlen(output)) * 0.3, -1, CV_COL32_WHITE, output);
    }
}