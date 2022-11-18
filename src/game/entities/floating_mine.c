#pragma once
#include "entities.h"
#include <stdlib.h>
#include "../tinkering.h"
struct entMF fmine [MINE_AMOUNT];
void mineInit()
{
    ImGuiIO* io = igGetIO();
    for(int i = 0; i < MINE_AMOUNT ; i++)
    {
        fmine[i].angle = rand() % 360;
        fmine[i].x = rand() % ((int)igGetIO()->DisplaySize.x / 50);
        fmine[i].y = -rand() % ((int)igGetIO()->DisplaySize.y / 50);
        fmine[i].momentumX = cosf(fmine[i].angle) * 0.1;
        fmine[i].momentumY = sinf(fmine[i].angle) * 0.1;
        
    }
}
void drawMineFloating(entMF currentMine)
{
    float2 points[6] = {
        { 0.1f * cosf(PI / 2), 0.1f * sinf(PI / 2)},
        { 0.5f * cosf(PI / 6), 0.5f * sinf(PI / 6)},
        { 0.1f * cosf(-PI / 6), 0.1f * sinf(-PI / 6)},
        { 0.5f * cosf(-PI / 2), 0.5f * sinf(-PI / 2)},
        { 0.1f * cosf(-5 * PI / 6), 0.1f * sinf(-5 * PI / 6)},
        { 0.5f * cosf((5 * PI) / 6), 0.5f * sinf((5 * PI) / 6)}
    };
        for (int j = 0; j < 6; ++j)
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
        
        fmine[i].x += fmine[i].momentumX * app -> deltaTime;
        fmine[i].y += fmine[i].momentumY * app -> deltaTime;     
    }
}