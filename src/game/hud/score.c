#include <string.h>
#include <stdio.h>
#include "../player/player.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>

void addScore(Player *player, int score)
{
	player->score += score;
}

//Draws the score on the HUD.
void drawHUDScore(Player *player, bool onTheLeft)
{
	char output[15]; //Max score can only contain 8 numbers. (99999999)
	sprintf(output, "Score: %d", player->score);
	ImGuiIO* io = igGetIO();
	if (onTheLeft)
	cvAddText(8/50, 0, CV_COL32_WHITE, output);
	else
		cvAddText((io->DisplaySize.x/50) - (strlen(output)) * 0.4,0, CV_COL32_WHITE, output);
}