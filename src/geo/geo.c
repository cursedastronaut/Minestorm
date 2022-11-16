#include "../app.h"
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
float2 rotatePoint(float2 p, float2 c, float angle)
{
    float2 r;
    r.x = (p.x-c.x) * cosf(angle) - (p.y-c.y) * sinf(angle) + c.x;
    r.y = (p.y-c.y) * cosf(angle) + (p.x-c.x) * sinf(angle) + c.y;
    return r;
}
/*
float2 midPt(float x1, float y1, float x2, float y2)
{
    float2 midPoint;
    midPoint = (float2){(x1 - x2) * 0.5f, (y1 - y2) * 0.5f};
    return midPoint;
}

void drawSquare(float2 p, float width, float angle)
{
    float2 points[4] = {
        { -0.5f,  0.5f },
        {  0.5f,  0.5f },
        {  0.5f, -0.5f },
        { -0.5f, -0.5f },
    };

    for (int i = 0; i < 4; ++i)
    {
        float2 newPoint = rotatePoint(points[i], angle);
        newPoint.x *= width;
        newPoint.y *= width;
        newPoint.x += p.x;
        newPoint.y += p.y;

        cvPathLineTo(newPoint.x, newPoint.y);
    }

    cvPathStroke(CV_COL32_WHITE, 1);
}

void drawTriangle(float2 p1, float2 p2, float2 p3)
{
    float2 points[3] = {
        { p1.x, p1.y },
        { p2.x, p2.y },
        { p3.x, p3.y },
    };
    for (int i = 0; i < 3; ++i)
    {
        float2 newPoint = points[i];
        cvPathLineTo(newPoint.x, newPoint.y);
    }

    cvPathStroke(CV_COL32_WHITE, 1);
}*/