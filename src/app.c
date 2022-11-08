#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>
#include <math.h>

#include "geo/geo.c"
#include "app.h"
#include "game/scenes/scenes.h"


void appInit(App* app)
{
}

//Handles the choosing of the chosen scene.
void sceneDisplay(App* app)
{
    switch (app->scene)
    {
    //Scene 0 = Main Menu
    case 0:
        displayMainMenu(app);
        processingMainMenu(app);
        break;

    //Scene 1 = Game
    case 1:
        displayGame(app);
        processingGame(app);
        break;
    default:
        break;
    }
}

void appUpdate(App* app)
{
    sceneDisplay(app);
    ImGuiIO* io = igGetIO();
    int width = io->DisplaySize.x;
    int height = io->DisplaySize.y;

    cvSetCoordinateSystemFromScreenSpace(
            0, 0, // origin
            50.f, 0.f,                 // right
            0.f, -50.f                 // top
    );
}

void appShutdown(App* app)
{
    (void)app; // TOREMOVE: Silence unused parameter ‘app’ warning
}