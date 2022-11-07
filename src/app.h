#pragma once
#include <stdbool.h>

typedef struct float2
{
    float x;
    float y;
} float2;

typedef struct HUD
{
    //TO EDIT | Player 1 & 2
    int score;  //Player score
    int lives;  //Lives left
} HUD;

typedef struct App
{
    struct HUD;
    int scene;
    bool shutdown;
} App;

void appInit(App* app);
void appUpdate(App* app);
void appShutdown(App* app);
