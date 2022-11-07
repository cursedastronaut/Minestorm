#pragma once
//#include <canvas.h>
#include "../../geo/text.c"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS


//Handles the Main Menu Display
void displayMainMenu(App* app)
{
    cvAddTextBorder(-1.5,7.9,CV_COL32_WHITE, "MINESTORM");
    cvAddTextBorder(-4,-7, CV_COL32_WHITE, "© GCE 1982 - ISART DIGITAL 2022");

    cvAddText(-3, 3, CV_COL32_WHITE, "F      -    New Game (1 player)");
    cvAddText(-3, 2, CV_COL32_WHITE, "K      -    New Game (2 players)");
    cvAddText(-3, 1, CV_COL32_WHITE, "ESC -    Quit");
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
    if (igIsKeyDown(ImGuiKey_F))
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
}