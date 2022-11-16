#pragma once
#define MAX_AMOUNT_OF_PLAYERS 2

typedef struct Player
{
    float x;
    float y;
    float angle;
    float momentumX;
    float momentumY;
    int score;
} Player;