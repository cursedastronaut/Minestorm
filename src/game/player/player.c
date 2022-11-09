#include "player.h"
#include <stdlib.h>
#include <time.h>
#define PI 3.14159276

pStruct player;
//Initializes the player's position
void playerInit(App* app)
{
    player.x = 10;
    player.y = -8;
}
//Draws the player to the screen
void drawPlayer(App* app)
{
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
}

void playerTeleport(App* app)
{
    ImGuiIO* io = igGetIO();
    srand( time(NULL) );
    player.x = rand();
    player.x /= RAND_MAX / 50;
    srand( time(0)-7 );
    player.y = -rand();
    player.y /= RAND_MAX / 50;

    if (player.x < 1)
    {
        player.x = 1;
    }
    if (player.y > -1)
        player.y=-1;
    if (player.y < -io->DisplaySize.y/50 )
        player.y= -io->DisplaySize.y/50 + 1;
    if (player.x > io->DisplaySize.x/50)
        player.x = io->DisplaySize.x/50-1;

}
//Checks for input and prepare for movement
void playerControls(App* app)
{
    //Controls
        if (igIsKeyDown(ImGuiKey_D) || igIsKeyDown(ImGuiKey_LeftArrow))
        {
            player.angle += (2.0f * PI / 360.0f) * app->deltaTime * 150;
        }
        if (igIsKeyDown(ImGuiKey_G) || igIsKeyDown(ImGuiKey_RightArrow))
        {
            player.angle -= (2.0f * PI / 360.0f) * app->deltaTime * 150;
        }
        if (igIsKeyDown(ImGuiKey_R) || igIsKeyDown(ImGuiKey_UpArrow))
        {
            // float velocity = sqrt(pow(player.momentumX, 2.0f) + pow(player.momentumY, 2.0f));
            // float direction = arccos(player.momentumX);
            // if (velocity > 0.2f)
            // {
            //     player.momentumX *= -cosf(player.angle);
            //     player.momentumY *= -sinf(player.angle);
            // }
            if (player.momentumX > 0.18f)
                player.momentumX = 0.18f;
            if (player.momentumX < -0.18f)
                player.momentumX = -0.18f;
            
            if (player.momentumY > 0.18f)
                player.momentumY = 0.18f;
            if (player.momentumY < -0.18f)
                player.momentumY = -0.18f;
            
            player.momentumX += (sin(-player.angle) * 0.005);
            player.momentumY += (cos(-player.angle) * 0.005);
        }

        if (igIsKeyDown(ImGuiKey_K))
        {
            playerTeleport(app);
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
}
//Actual movement processing
void playerMovement(App* app)
{
    //Movement
    player.x += player.momentumX * app->deltaTime * 30;
    player.y += player.momentumY * app->deltaTime * 30;
}
//Friction processing
void playerFrictions(App* app)
{
    //Friction
    player.momentumX *= 0.99f;
    player.momentumY *= 0.99f;
}
//Checks if player is Out Of Bounds and moves him to the other side if yes
void playerOOB(App* app)
{
    ImGuiIO* io = igGetIO();
    //Out of borders
    if (player.x > io->DisplaySize.x / 50 + 1)
        player.x = -0.5;
    if (player.x < -1)
        player.x = io->DisplaySize.x / 50 + 0.5;

    if (player.y < -io->DisplaySize.y / 50 - 2 )
        player.y = 0.5;
    if (player.y > 1)
        player.y = -io->DisplaySize.y / 50 - 0.5;
}
//Displays debug informations
void playerDebug(App* app)
{
    //Debug
    igText("DeltaTime: %f", app->deltaTime);
    igText("Player 1");
    igText("X: %f", player.x);
    igText("Y: %f", player.y);
    igText("Speed: %f", sqrt(pow(player.momentumX, 2.0f) + pow(player.momentumY, 2.0f)));
    igText("Momentum X: %f", player.momentumX);
    igText("Momentum Y: %f", player.momentumY);
    igText("Angle: %f", player.angle);
}
//Unites all of the above functions
void playerScript(App* app)
{
    drawPlayer(app);
    playerControls(app);
    playerFrictions(app);
    playerMovement(app);
    playerOOB(app);
    playerDebug(app);
}