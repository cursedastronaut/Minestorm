#pragma once
#include "entity_type.c"
#include <toolbox.h>
#include <stdbool.h>

extern const float2 pointsFireball[8];
extern const float2 pointsFire[8];
extern const float2 pointsFloat[6];
extern const float2 pointsFiremag[8];
extern const float2 pointsMagnetic[8];

typedef struct Mine
{
    int   type;         //Type of mine
    float x;            //Mine's X position
    float y;            //Mine's Y position
    float angle;        //Mine's angle
    float momentumX;    //Mine's X momentum
    float momentumY;    //Mine's Y momentum
    int   size;
    bool  isActive;
} Mine;

void entityMineUpdate(App* app);
void entityType();
void mineInit();