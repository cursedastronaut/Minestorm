#pragma once
#include "player_shot.c"
#include "fireball_mine.c"
#include "magnetic_fireball_mine.c"
#include "magnetic_mine.c"
//#include "player_shot.c"

typedef struct entMF
{
    float x;
    float y;
    float angle;
    float momentumX;
    float momentumY;
} entMF;

void entityMineFloating();