#include "player.h"
#define PI 3.14159276

pStruct player;

// float2 rotatePoint(float2 p, float angle)
// {
//     float2 r;
//     r.x = p.x * cosf(angle) - p.y * sinf(angle);
//     r.y = p.y * cosf(angle) + p.x * sinf(angle);
//     return r;
// }

void playerScript()
{
    float2 points[6] = {
        { 3.0f, -2.0f },
        { 4.0f, -4.0f },
        { 3.5f, -3.5f },
        { 3.0f, -3.75f },
        { 2.5f, -3.5f },
        { 2.0f, -4.0f },
    };
    for (int i = 0; i < 6; ++i)
    {
        float2 newPoint = points[i];
        float2 temp = newPoint;
        newPoint.x = rotatePoint(temp, points[0], player.angle).x + player.x;
        newPoint.y = rotatePoint(temp, points[0], player.angle).y + player.y;

        cvPathLineTo(newPoint.x, newPoint.y);
    }
    cvPathStroke(CV_COL32_WHITE, 1);

    /*if (igIsKeyDown(ImGuiKey_UpArrow))
    {
        player.x += 0.02f * cosf((player.angle + 90.0f) / (360 / (2 * M_PI)));
        player.y += 0.02f * sinf((player.angle + 90.0f) / (360 / (2 * M_PI)));
    }
    if (igIsKeyDown(ImGuiKey_DownArrow))
    {
        player.x -= 0.02f * cosf((player.angle + 90.0f) / (360 / (2 * M_PI)));
        player.y -= 0.02f * sinf((player.angle + 90.0f) / (360 / (2 * M_PI)));
    }*/




    //Controls
    if (igIsKeyDown(ImGuiKey_D))
    {
        player.angle -= (2.0f * PI / 360.0f) * 4;
    }
    if (igIsKeyDown(ImGuiKey_G))
    {
        player.angle += (2.0f * PI / 360.0f) * 4;
    }
    if (igIsKeyDown(ImGuiKey_R))
    {
        player.x += (sin(-player.angle) * 1);
        player.y += (cos(-player.angle) * 1);
    }

    //Angle
    if (player.angle > 2.0f * PI)
    {
        player.angle = 0.0f;
    }
    else if (player.angle < 0.0f)
    {
        player.angle = 2.0f * PI;
    }
    cvAddFormattedText(5,-5,CV_COL32_WHITE, "Angle: %f", player.angle);
}