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
    srand(time(NULL));
    playerInit(app);
    app->graphics.textures.logo = cvLoadTexture("assets/minestorm-original.png");
    app->graphics.textures.window[0] = cvLoadTexture("assets/window.png");
    app->graphics.textures.window[1] = cvLoadTexture("assets/window1.png");
    app->graphics.textures.controls = cvLoadTexture("assets/controls.png");
    app->graphics.show_static = true;
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