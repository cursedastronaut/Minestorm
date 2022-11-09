#pragma once
#include "entities.h"
entMF fmine;
void drawMineFloating()
{
    float2 points[6] = {
        { 0.1f * cosf(PI / 2), 0.1f * sinf(PI / 2)},
        { 0.5f * cosf(PI / 6), 0.5f * sinf(PI / 6)},
        { 0.1f * cosf(-PI / 6), 0.1f * sinf(-PI / 6)},
        { 0.5f * cosf(-PI / 2), 0.5f * sinf(-PI / 2)},
        { 0.1f * cosf(-5 * PI / 6), 0.1f * sinf(-5 * PI / 6)},
        { 0.5f * cosf((5 * PI) / 6), 0.5f * sinf((5 * PI) / 6)}
    };
    for (int i = 0; i < 6; ++i)
    {
        float2 newPoint = points[i];
        newPoint.x *= 2.0f;
        newPoint.y *= 2.0f;
        float2 temp = newPoint;
        newPoint.x = rotatePoint(temp, points[0], fmine.angle).x + fmine.x;
        newPoint.y = rotatePoint(temp, points[0], fmine.angle).y + fmine.y;

        cvPathLineTo(newPoint.x, newPoint.y); 
    }
    cvPathStroke(CV_COL32_WHITE, 1);
}

void entityMineFloating(App* app)
{
    drawMineFloating();
        //Movement
        fmine.momentumX = 0.01;
        fmine.momentumY = -0.01;
        fmine.x += fmine.momentumX;
        fmine.y += fmine.momentumY;
}