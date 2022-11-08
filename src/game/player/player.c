#include "player.h"
#define PI 3.14159276

pStruct player;
//s'exécute une fois lors du lancement du jeu
void playerInit(App* app)
{
    player.x = 10;
    player.y = -8;
}
//s'exécute en continu
void playerScript(App* app)
{
    ImGuiIO* io = igGetIO();
    int width = io->DisplaySize.x;
    int height = io->DisplaySize.y;
    float2 points[6] = {
        { 0.0f, 0.5f },
        { 0.5f, -0.3f },
        { 0.35f, -0.3f },
        { 0.0f, -0.5f },
        { -0.35f, -0.3f },
        { -0.5f, -0.3f },
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

    if (app->deltaTime >= 1.0f/60.0f)
    {
        
        //Controls
        if (igIsKeyDown(ImGuiKey_D) || igIsKeyDown(ImGuiKey_LeftArrow))
        {
            player.angle += (2.0f * PI / 360.0f) * 5;
        }
        if (igIsKeyDown(ImGuiKey_G) || igIsKeyDown(ImGuiKey_RightArrow))
        {
            player.angle -= (2.0f * PI / 360.0f) * 5;
        }
        if (igIsKeyDown(ImGuiKey_R) || igIsKeyDown(ImGuiKey_UpArrow))
        {
            if (player.momentumX > 0.2f)
                player.momentumX = 0.2f;
            if (player.momentumX < -0.2f)
                player.momentumX = -0.2f;
            
            if (player.momentumY > 0.2f)
                player.momentumY = 0.2f;
            if (player.momentumY < -0.2f)
                player.momentumY = -0.2f;
            
            player.momentumX += (sin(-player.angle) * 0.01);
            player.momentumY += (cos(-player.angle) * 0.01);
        }

        //friction
        player.momentumX *= 0.97f;
        player.momentumY *= 0.97f;

        //angle
        if (player.angle > 2.0f * PI)
        {
            player.angle = 0.0f;
        }
        else if (player.angle < 0.0f)
        {
            player.angle = 2.0f * PI;
        }

        //movement
        player.x += player.momentumX;
        player.y += player.momentumY;
        app->deltaTime = 0;
    }


    //Out of borders
    if (player.x > io->DisplaySize.x / 50)
        player.x = 0;
    if (player.x < 0)
        player.x = io->DisplaySize.x / 50;

    if (player.y < -io->DisplaySize.y / 50)
        player.y = 0;
    if (player.y > 0)
        player.y = -io->DisplaySize.y / 50;

    cvAddFormattedText(5,-5,CV_COL32_WHITE, "Angle: %f", player.angle);
    cvAddFormattedText(5,-6,CV_COL32_WHITE, "MomX: %f", player.momentumX);
    cvAddFormattedText(5,-7,CV_COL32_WHITE, "MomY: %f", player.momentumY);
}