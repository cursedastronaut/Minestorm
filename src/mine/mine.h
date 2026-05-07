#pragma once
#include <toolbox.h>
#include <stdbool.h>
#include "../app.h"

extern const float2 pointsFireball[8];
extern const float2 pointsFire[8];
extern const float2 pointsFloat[6];
extern const float2 pointsFiremag[8];
extern const float2 pointsMagnetic[8];

extern int chanceMineFloating;
extern int chanceMineFireball;
extern int chanceMineMagnetic;
extern int chanceMineFiremag;

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