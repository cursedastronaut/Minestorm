#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>
#include <math.h>
#include "geo/geo.c"
#include "app.h"

void appInit(App* app)
{
    /**app = (App){0};
    app->time = 0.0f;
    app->position = (float2){ 0.f, 0.f };
    app->p1Pos = (float2){ sqrtf(3) * 0.5f, -0.5f };
    app->p2Pos = (float2){ 0.0f, 1.0f };
    app->p3Pos = (float2){ -sqrtf(3) * 0.5f, -0.5f };
    app->width = 2.0f;
    app->spinSpeed = 1.0f;*/
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