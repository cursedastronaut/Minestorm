#include "../player/player.h"
#include "../../app.h"
#include <stdio.h>
#include <string.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>

void drawHUDLivesLeft(Player *player, bool onTheLeft)
{
	if (onTheLeft)
	    cvAddFormattedText(0,-1, CV_COL32_WHITE, "P1 Li%s: %d", player->lives > 1 ? "ves" : "fe",player->lives);
    else
    {
        char output[15];
        sprintf(output, "P2 Li%s: %d", player->lives > 1 ? "ves" : "fe",player->lives);
        cvAddFormattedText(( igGetIO()->DisplaySize.x/50 ) - (strlen(output)) * 0.3, -1, CV_COL32_WHITE, output);
    }
}