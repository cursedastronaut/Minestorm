#pragma once
#include "../../geo/text.c"
#include "../../app.h"
#include "../../graphics/static.c"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS


//Handles the Main Menu Display
void displayMainMenu(App* app)
{
    ImGuiIO* io = igGetIO();
    cvAddTextBorder((io->DisplaySize.x/50) / 2 - 3.4, -io->DisplaySize.y/50+1, CV_COL32_WHITE, "© GCE 1982 - ISART DIGITAL 2022");
    if (app->animtime % 2 == 0)
        app->anim = !app->anim;
    if (app->anim)
        cvAddTexture((io->DisplaySize.x/50) / 2, - (io->DisplaySize.y/50)/2, app->textures.window[0]);
    else
        cvAddTexture((io->DisplaySize.x/50) / 2, - (io->DisplaySize.y/50)/2, app->textures.window[1]);
    cvAddTexture((io->DisplaySize.x/50) / 2, -2, app->textures.logo);
}



//Handles the Main Menu Processing
void processingMainMenu(App* app)
{
    //Lance une partie solo
    if (igIsKeyDown(ImGuiKey_F))
    {
        app->twoPlayers = false;
        app->scene = 1;
        printf("app->scene = 1\n");
    }

    //Lance une partie deux joueurs
    if (igIsKeyDown(ImGuiKey_K))
    {
        app->twoPlayers = true;
        app->scene = 1;
        printf("app->scene = 1\n");
    }

    //Quitte le jeu
    if (igIsKeyDown(ImGuiKey_Escape))
    {
        app->shutdown = true;
    }

    if (igIsKeyReleased(ImGuiKey_V))
    {
        app->graphics.show_static = !app->graphics.show_static;
    }
}