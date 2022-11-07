#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>
#include <math.h>

#include "app.h"

float2 rotatePoint(float2 p, float angle)
{
    float2 r;
    r.x = p.x * cosf(angle) - p.y * sinf(angle);
    r.y = p.y * cosf(angle) + p.x * sinf(angle);
    return r;
}

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
}

void appInit(App* app)
{
    *app = (App){0};
    app->time = 0.0f;
    app->position = (float2){ 0.f, 0.f };
    app->p1Pos = (float2){ sqrtf(3) * 0.5f, -0.5f };
    app->p2Pos = (float2){ 0.0f, 1.0f };
    app->p3Pos = (float2){ -sqrtf(3) * 0.5f, -0.5f };
    app->width = 2.0f;
    app->spinSpeed = 1.0f;
}

void appUpdate(App* app)
{
    ImGuiIO* io = igGetIO();
    int width = io->DisplaySize.x;
    int height = io->DisplaySize.y;

    cvSetCoordinateSystemFromScreenSpace(
            width / 2.f, height / 2.f, // origin
            50.f, 0.f,                 // right
            0.f, -50.f                 // top
    );

    // igShowDemoWindow(NULL);
    // igDragFloat("Width", &app->width, 0.1f, 0.f, 10.f, "%.1f", 0);
    // igDragFloat2("P1", &app->p1Pos, 0.1f, -10.f, 10.f, "%.1f", 0);
    // igDragFloat2("P2", &app->p2Pos, 0.1f, -10.f, 10.f, "%.1f", 0);
    // igDragFloat2("P3", &app->p3Pos, 0.1f, -10.f, 10.f, "%.1f", 0);
    // igSliderAngle("Rotation", &app->angle, 0.1f, 360.f, "%.2f", 0);
    // igSliderInt("Iterations", &app->iteration, 0, 7, "%1f", 0);
    // igCheckbox("Is spinning?", &app->isSpinning);
    // igSliderFloat("Spinning speed", &app->spinSpeed, 1.f, 100.f, "%.1f", 0);
    // igCheckbox("Spin counter-clockwise", &app->clockwiseSpin);
}

void appShutdown(App* app)
{
    (void)app; // TOREMOVE: Silence unused parameter ‘app’ warning
}