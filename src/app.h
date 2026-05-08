#pragma once
#ifndef APP_H
#define APP_H
#include <stdbool.h>
#include <canvas.h>
#include "audio.h"
#include "game/bullet.h"
#include "game/game.h"
#include <miniaudio.h>
#include <toolbox.h>
#include "game/player/player.h"

typedef struct textures
{
    CvTexture logo;
    CvTexture window;
    CvTexture controls;
    CvTexture forcefield;
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

	Player player[2];
	Bullet bullets[MAX_BULLET_COUNT];

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

#endif