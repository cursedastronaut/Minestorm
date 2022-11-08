#include "player.h"


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
        { 0.0f, 1.0f },
        { 1.0f, -1.0f },
        { 0.5f, -0.5f },
        { 0.0f, -0.75f },
        { -0.5f, -0.5f },
        { -1.0f, -1.0f },
    };
    for (int i = 0; i < 6; ++i)
    {
        float2 newPoint = points[i];
        newPoint.x = rotatePoint(newPoint, player.angle).x + player.x;
        newPoint.y = rotatePoint(newPoint, player.angle).y + player.y;

        cvPathLineTo(newPoint.x, newPoint.y);
    }
    cvPathStroke(CV_COL32_WHITE, 1);

    if (igIsKeyDown(ImGuiKey_UpArrow))
    {
        player.x += 0.02f * cosf((player.angle + 90.0f) / (360 / (2 * M_PI)));
        player.y += 0.02f * sinf((player.angle + 90.0f) / (360 / (2 * M_PI)));
    }
        if (igIsKeyDown(ImGuiKey_DownArrow))
    {
        player.x -= 0.02f * cosf((player.angle + 90.0f) / (360 / (2 * M_PI)));
        player.y -= 0.02f * sinf((player.angle + 90.0f) / (360 / (2 * M_PI)));
    }
        if (igIsKeyDown(ImGuiKey_LeftArrow))
    {
        player.angle -= 0.01f;
    }
        if (igIsKeyDown(ImGuiKey_RightArrow))
    {
        player.angle += 0.01f;
    }
    
    if (player.angle > 360.0f)
    {
        player.angle = 0.0f;
    }
    else if (player.angle < 0.0f)
    {
        player.angle = 360.0f;
    }
}