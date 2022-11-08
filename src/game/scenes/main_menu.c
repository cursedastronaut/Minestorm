#pragma once
//#include <canvas.h>
#include "../../geo/text.c"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS


//Handles the Main Menu Display
void displayMainMenu(App* app)
{
    ImGuiIO* io = igGetIO();
    cvAddTextBorder((io->DisplaySize.x/50) / 2 - 1.5, io->DisplaySize.y/50,CV_COL32_WHITE, "MINESTORM");
    cvAddTextBorder((io->DisplaySize.x/50) / 2 - 3.4, 1, CV_COL32_WHITE, "© GCE 1982 - ISART DIGITAL 2022");

    cvAddText((io->DisplaySize.x/50) / 2 - 4, 10, CV_COL32_WHITE, "F      -    New Game (1 player)");
    cvAddText((io->DisplaySize.x/50) / 2 - 4, 9, CV_COL32_WHITE, "K      -    New Game (2 players)");
    cvAddText((io->DisplaySize.x/50) / 2 - 4, 8, CV_COL32_WHITE, "ESC -    Quit");
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