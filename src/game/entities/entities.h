#pragma once
#include "player_shot.c"
#include "fireball_mine.c"
#include "magnetic_fireball_mine.c"
#include "magnetic_mine.c"
#include "entity_type.c"

typedef struct entMF
{
    float type;         //Type of mine
    float x;            //Mine's X position
    float y;            //Mine's Y position
    float angle;        //Mine's angle
    float momentumX;    //Mine's X momentum
    float momentumY;    //Mine's Y momentum
} entMF;

void entityMineFloating();
void entityType();