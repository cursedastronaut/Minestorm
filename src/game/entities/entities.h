#pragma once
#include "fireball_mine.c"
#include "magnetic_fireball_mine.c"
#include "magnetic_mine.c"
#include "floating_mine.c"
#include "fireball.c"
#include "entity_type.c"

typedef struct entMF
{
    int type;         //Type of mine
    float x;            //Mine's X position
    float y;            //Mine's Y position
    float angle;        //Mine's angle
    float momentumX;    //Mine's X momentum
    float momentumY;    //Mine's Y momentum
    int size;
    bool isActive;
} entMF;

void entityMineUpdate();
void entityType();