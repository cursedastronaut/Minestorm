#pragma once
#include "player_shot.c"
#include "fireball_mine.c"
#include "magnetic_fireball_mine.c"
#include "magnetic_mine.c"
#include "entity_type.c"
//#include "player_shot.c"

typedef struct entMF
{
    float type;         //Type of mine
    float x;            //Mine's X position
    float y;            //Mine's Y position
    float angle;        //Mine's angle (Useless)
    float momentumX;    //Mine's X momentum
    float momentumY;    //Mine's Y momentum
    //struct entMF next;
} entMF;

void entityMineFloating();
void entityType();