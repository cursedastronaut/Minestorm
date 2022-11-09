#pragma once
#include "entities.h"
entMF fmine;
void drawMineFloating()
{
    float2 points[6] = {
        { 0.0f, 0.3f },
        { 0.5f, -0.3f },
        { 0.35f, -0.3f },
        { 0.0f, -0.5f },
        { -0.35f, -0.3f },
        { -0.5f, -0.3f },
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
    if (app->deltaTime >= 1.0f/60.0f)
    {
        //Movement
        fmine.momentumX = 0.04;
        fmine.momentumY = -0.04;
        fmine.x += fmine.momentumX;
        fmine.y += fmine.momentumY;
    }

}