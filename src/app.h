#pragma once
#include <stdbool.h>

typedef struct float2
{
    float x;
    float y;
} float2;

typedef struct App
{
    bool movePoint;
    float time;
    float2 position;
    float2 p1Pos;
    float2 p2Pos;
    float2 p3Pos;
    float width;
    float angle;
    float spinSpeed;
    int iteration;
    bool isSpinning;
    bool clockwiseSpin;
} App;

void appInit(App* app);
void appUpdate(App* app);
void appShutdown(App* app);
