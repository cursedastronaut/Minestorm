#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>
#include <time.h>
#include <math.h>
#include "geo/geo.c"            //Moteur de jeu
#include "app.h"                //Db
#include "game/scenes/scenes.h" //Liste des scènes


void appInit(App* app)
{
    app->paused = false;
    srand(time(NULL));      //Initial srand
    app->graphics.textures.logo = cvLoadTexture("assets/minestorm-original.png");   //Loading the logo
    app->graphics.textures.window = cvLoadTexture("assets/window.png");             //Loading the menu window
    app->graphics.textures.controls = cvLoadTexture("assets/controls.png");         //Loads controls window
    app->graphics.textures.gameOver = cvLoadTexture("assets/game_over.png");         //Loads controls window
    app->graphics.textures.copyright = cvLoadTexture("assets/copyright.png");         //Loads copyright text
    app->graphics.show_static = false;
    app->sceneMainMenu.show_controls = false;
    playerInit(app);
}

//Handles the choosing of the chosen scene.
void sceneDisplay(App* app)
{
    app->deltaTime = igGetIO()->DeltaTime;
    switch (app->scene)
    {
    //Scene 0 = Main Menu
    case 0:
        displayMainMenu(app);
        processingMainMenu(app);
        break;

    //Scene 1 = Game
    case 1:
        gameInit(app);
        displayGame(app);
        processingGame(app);
        break;
    
    //Game Over
    case 3:
        displayGameOver(app);
        break;

    default:
        break;
    }
    staticDisplay(app);
}

void appUpdate(App* app)
{
    ImGuiIO* io = igGetIO();
    sceneDisplay(app);
    // app -> width = io->DisplaySize.x;
    // app -> height = io->DisplaySize.y;

    cvSetCoordinateSystemFromScreenSpace(
            0, 0, // origin
            50.0f, 0.f,                 // right
            0.f, -50.0f                 // top
    );
}

void appShutdown(App* app)
{
    (void)app; // TOREMOVE: Silence unused parameter ‘app’ warning
}