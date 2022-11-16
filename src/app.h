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

typedef struct textures
{
    CvTexture logo;
    CvTexture window[2];
    CvTexture staticE [21];
    int staticA;
} textures;

typedef struct App
{
    struct HUD HUD;
    struct textures textures;

    bool paused;

    int scene;
    bool shutdown;
    bool twoPlayers;

    float deltaTime;

    int width;
    int height;

    bool anim;
    int animtime;
} App;

void appInit(App* app);
void appUpdate(App* app);
void appShutdown(App* app);
