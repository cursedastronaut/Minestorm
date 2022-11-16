#pragma once
#include <stdbool.h>

typedef struct float2
{
    float x;
    float y;
} float2;

typedef struct textures
{
    CvTexture logo;
    CvTexture window[2];
    CvTexture controls;
    CvTexture staticE [21];
    int staticA;
} textures;

typedef struct graphics
{
    struct textures textures;
    bool show_static;
} graphics;

typedef struct App
{
    struct graphics graphics;

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
