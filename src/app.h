#pragma once
#include <stdbool.h>
#include "audio.h"
#include <miniaudio.h>

typedef struct float2
{
    float x;
    float y;
} float2;

typedef struct textures
{
    CvTexture logo;
    CvTexture window;
    CvTexture controls;
    CvTexture gameOver;
    CvTexture copyright;
    CvTexture staticE [21];
    int staticA;
} textures;

typedef struct graphics
{
    struct textures textures;
    bool show_static;
    bool show_collisionbox;
} graphics;

typedef struct sceneMainMenu
{
    bool show_controls;
} sceneMainMenu;

typedef struct App
{
    struct graphics graphics;
    struct sceneMainMenu sceneMainMenu;

    bool paused;

    int scene;
    bool shutdown;
    bool twoPlayers;

    float deltaTime;

    int width;
    int height;

    int animtime;
    bool gameinit;
    ma_result result;
    ma_engine engine;
    int bestScoreSingleplayer;
    int bestScoreMultiplayer[2];
} App;

void appInit(App* app);
void appUpdate(App* app);
void appShutdown(App* app);
