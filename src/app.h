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
    int p1_score;  //Player score
    int p1_lives;  //Lives left
    int p2_score;
    int p2_lives;
} HUD;

typedef struct App
{
    struct HUD HUD;

    bool paused;

    int scene;
    bool shutdown;
    bool twoPlayers;

    float deltaTime;
} App;

void appInit(App* app);
void appUpdate(App* app);
void appShutdown(App* app);
