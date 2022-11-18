#pragma once
#include "entities.h"
#include <stdlib.h>
#include "../tinkering.h"
struct entMF fmine [MINE_AMOUNT];   //Choosing the amount of mines (see tinkering.h)
void mineInit()
{
    ImGuiIO* io = igGetIO();
    for(int i = 0; i < MINE_AMOUNT ; i++) //Looping through all the mines
    {
        fmine[i].angle = rand() % 360;                                  //Sets a random angle
        fmine[i].x = rand() % ((int)igGetIO()->DisplaySize.x / 50);     //Sets a random position on the X axis (within the window's limits)
        fmine[i].y = -rand() % ((int)igGetIO()->DisplaySize.y / 50);    //Sets a random position on the Y axis (within the window's limits)
        fmine[i].momentumX = cosf(fmine[i].angle) * 0.1;                //Sets the momentum variables so that it goes
        fmine[i].momentumY = sinf(fmine[i].angle) * 0.1;                //in the direction of its angle.
        
    }
}
void drawMineFloating(entMF currentMine)
{
    //Shape
    float2 points[6] = {
        { 0.1f * cosf(PI / 2), 0.1f * sinf(PI / 2)},            
        { 0.5f * cosf(PI / 6), 0.5f * sinf(PI / 6)},
        { 0.1f * cosf(-PI / 6), 0.1f * sinf(-PI / 6)},
        { 0.5f * cosf(-PI / 2), 0.5f * sinf(-PI / 2)},
        { 0.1f * cosf(-5 * PI / 6), 0.1f * sinf(-5 * PI / 6)},
        { 0.5f * cosf((5 * PI) / 6), 0.5f * sinf((5 * PI) / 6)}
    };
        for (int j = 0; j < 6; ++j)     //Looping through the points
        {
            float2 newPoint = points[j];
            newPoint.x *= 2.0f;
            newPoint.y *= 2.0f;
            newPoint.x += currentMine.x;
            newPoint.y += currentMine.y;

            cvPathLineTo(newPoint.x, newPoint.y); 
        }
        cvPathStroke(CV_COL32_WHITE, 1);
}

void entityMineFloating(App* app)
{
    //Movement
    for (int i = 0; i < MINE_AMOUNT; i++)
    {
        drawMineFloating(fmine[i]);
        
        fmine[i].x += fmine[i].momentumX * app -> deltaTime; //Make it move.
        fmine[i].y += fmine[i].momentumY * app -> deltaTime;     
    }
}