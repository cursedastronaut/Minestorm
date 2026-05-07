#pragma once
#ifndef		PLAYER_H
# define	PLAYER_H
# include	"../../app.h"
# include "../tinkering.h"


typedef struct Player
{
    float x;
    float y;
    float angle;
    float momentumX;
    float momentumY;
    int score;
    int lives;
    float invincibility;
} Player;

extern Player gPlayers [MAX_AMOUNT_OF_PLAYERS];

void playerInit(App* app);
void playerScript(App* app);


void killPlayer(int index, App* app);
#endif