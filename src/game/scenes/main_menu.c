#pragma once
#include "../../geo/text.c"
#include "../../app.h"
#include "../../graphics/static.c"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS


//Handles the Main Menu Display
void displayMainMenu(App* app)
{
    ImGuiIO* io = igGetIO();
    cvAddTexture(   (io->DisplaySize.x/50) / 2,     -2,                         app->graphics.textures.logo);       //Draws the logo.
    cvAddTexture(   (io->DisplaySize.x/50) / 2,     -(io->DisplaySize.y/50)+1,  app->graphics.textures.copyright);  //Here, I use a texture instead of a text because it centers by itself.
    if (app->sceneMainMenu.show_controls == false)
        cvAddTexture((io->DisplaySize.x/50) / 2,    - (io->DisplaySize.y/50)/2, app->graphics.textures.window);
    else
        cvAddTexture((io->DisplaySize.x/50) / 2,    - (io->DisplaySize.y/50)/2, app->graphics.textures.controls);
    
    
    if (igIsKeyPressed(ImGuiKey_C, 0))
        app->sceneMainMenu.show_controls = !app->sceneMainMenu.show_controls;
}



//Handles the Main Menu Processing
void processingMainMenu(App* app)
{
    //Lance une partie solo
    if (igIsKeyPressed(ImGuiKey_F, 0))
    {
        app->twoPlayers = false;
        app->scene = 1;
        printf("app->scene = 1\n");
    }

    //Lance une partie deux joueurs
    if (igIsKeyPressed(ImGuiKey_K, 0))
    {
        app->twoPlayers = true;
        app->scene = 1;
        printf("app->scene = 1\n");
    }

    //Quitte le jeu
    if (igIsKeyPressed(ImGuiKey_Escape, 0))
    {
        app->shutdown = true;
    }

    if (igIsKeyPressed(ImGuiKey_V, 0))
    {
        app->graphics.show_static = !app->graphics.show_static;
    }
}