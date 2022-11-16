#include "player.h"
#include "../entities/bullet.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define PI 3.14159276
#define MAX_BULLET_COUNT 256
#define BULLET_LIFE_TIME 5

Player gPlayers [MAX_AMOUNT_OF_PLAYERS];
Bullet gBullets [MAX_BULLET_COUNT];

//Initializes the player's position
void playerInit(App* app)
{
    gPlayers[0].x = 12.5;
    gPlayers[0].y = -7;
    gPlayers[1].x = 7.5;
    gPlayers[1].y = -7;
    for (int i = 0; i < MAX_BULLET_COUNT; i++)
    {
        gBullets[i].isActive = 0;
        gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME;
    }
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
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 6; ++i)
        {
            float2 newPoint = points[i];
            float2 temp = newPoint;
            float2 xy = {0, 0};
            newPoint.x = rotatePoint(temp, xy, gPlayers[j].angle).x + gPlayers[j].x;
            newPoint.y = rotatePoint(temp, xy, gPlayers[j].angle).y + gPlayers[j].y;

            cvPathLineTo(newPoint.x, newPoint.y);
        }
        cvPathStroke(CV_COL32_WHITE, 1);
    }
    cvAddPoint(gPlayers[0].x, gPlayers[0].y, CV_COL32(255,0,0,255));
    cvAddPoint(gPlayers[1].x, gPlayers[1].y, CV_COL32(0,255,0,255));
}

void playerTeleport(App* app)
{
    ImGuiIO* io = igGetIO();
    gPlayers[0].x = rand() % ((int) io->DisplaySize.x / 50);
    gPlayers[0].y = -rand() % ((int) io->DisplaySize.y / 50);
}

bool fireBullet(int p)
{
    float oldestBullet = BULLET_LIFE_TIME;
    int oldestBulletIndex = -1;
    for (int i = 0; i < MAX_BULLET_COUNT; i++)
    {
        if (gBullets[i].isActive == 0)
        {
            gBullets[i].isActive = 1;
            gBullets[i].x = gPlayers[p].x;
            gBullets[i].y = gPlayers[p].y;
            gBullets[i].angle = gPlayers[p].angle;
            return 0;
        }
        if (gBullets[i].timeBeforeDeath < oldestBullet)
        {
            oldestBullet = gBullets[i].timeBeforeDeath;
            oldestBulletIndex = i;
        }
    }

    if (oldestBulletIndex != -1)
    {
        gBullets[oldestBulletIndex].x = gPlayers[p].x;
        gBullets[oldestBulletIndex].y = gPlayers[p].y;
        gBullets[oldestBulletIndex].timeBeforeDeath = 3;
        gBullets[oldestBulletIndex].angle = gPlayers[p].angle;
    }
    return 0;
}
void bulletUpdate(App* app)
{
    ImGuiIO* io = igGetIO();
    for (int i = 0; i < MAX_BULLET_COUNT; i++)
    {
        if (gBullets[i].isActive == 1)
        {
            gBullets[i].x += cosf(gBullets[i].angle + (PI / 2)) * app -> deltaTime * 10;
            gBullets[i].y += sinf(gBullets[i].angle + (PI / 2)) * app -> deltaTime * 10;
            gBullets[i].timeBeforeDeath -= app -> deltaTime;
            cvAddPoint(gBullets[i].x, gBullets[i].y, CV_COL32_WHITE);

            if (gBullets[i].timeBeforeDeath <= 0)
            {
                gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME;
                gBullets[i].isActive = 0;
            }
        
            if (gBullets[i].x > io->DisplaySize.x / 50 + 1)
                gBullets[i].x = -0.5;
            if (gBullets[i].x < -1)
                gBullets[i].x = io->DisplaySize.x / 50 + 0.5;

            if (gBullets[i].y < -io->DisplaySize.y / 50 - 2 )
                gBullets[i].y = 0.5;
            if (gBullets[i].y > 1)
                gBullets[i].y = -io->DisplaySize.y / 50 - 0.5;
        }
    }
}
void bulletDebug()
{
    int bulletCount = 0;
    for (int i = 0; i < MAX_BULLET_COUNT; i++)
    {
        if (gBullets[i].isActive == true)
        {
            bulletCount ++;
        }
    }
    igText("Drawn Bullets: %d | Max: %d", bulletCount, MAX_BULLET_COUNT);
}


//Checks for input and prepare for movement
void playerControls(App* app)
{
    //PLAYER 1
        if (igIsKeyDown(ImGuiKey_D) || igIsKeyDown(ImGuiKey_LeftArrow))
        {
            gPlayers[0].angle += (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_G) || igIsKeyDown(ImGuiKey_RightArrow))
        {
            gPlayers[0].angle -= (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_R) || igIsKeyDown(ImGuiKey_UpArrow))
        {   
            gPlayers[0].momentumX += (sin(-gPlayers[0].angle) * 0.25f);
            gPlayers[0].momentumY += (cos(-gPlayers[0].angle) * 0.25f);
        }

        if (igIsKeyReleased(ImGuiKey_K))
        {
            playerTeleport(app);
        }
        if (igIsKeyReleased(ImGuiKey_N))
        {
            fireBullet(0);
        }
    
    //PLAYER 2
        if (igIsKeyDown(ImGuiKey_Keypad4))
        {
            gPlayers[1].angle += (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_Keypad6))
        {
            gPlayers[1].angle -= (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_Keypad8))
        {   
            gPlayers[1].momentumX += (sin(-gPlayers[1].angle) * 0.25f);
            gPlayers[1].momentumY += (cos(-gPlayers[1].angle) * 0.25f);
        }
        
        if (igIsKeyReleased(ImGuiKey_K))
        {
            playerTeleport(app);
        }
        if (igIsKeyReleased(ImGuiKey_B))
        {
            fireBullet(1);
        }

        //Angle
        for (int i = 0; i < 2; i++)
        {
            if (gPlayers[i].angle > 2.0f * PI)
            {
                gPlayers[i].angle = 0.0f;
            }
            else if (gPlayers[i].angle < 0.0f)
            {
                gPlayers[i].angle = 2.0f * PI;
            }
        }
        
}
//Actual movement processing
void playerMovement(App* app)
{
    //Movement
    for (int i = 0; i < 2; i++)
    {
        gPlayers[i].x += gPlayers[i].momentumX * app->deltaTime;
        gPlayers[i].y += gPlayers[i].momentumY * app->deltaTime;
    }
}
//Friction processing
void playerFrictions(App* app)
{
    //Friction
    for (int i = 0; i < 2; i++)
    {
        gPlayers[i].momentumX *= 0.98f;
        gPlayers[i].momentumY *= 0.98f;
    }
}
//Checks if player is Out Of Bounds and moves him to the other side if yes
void playerOOB(App* app)
{
    ImGuiIO* io = igGetIO();
    //Out of borders
    for (int i = 0; i < 2; i++)
    {
        if (gPlayers[i].x > io->DisplaySize.x / 50 + 1)
            gPlayers[i].x = -0.5;
        if (gPlayers[i].x < -1)
            gPlayers[i].x = io->DisplaySize.x / 50 + 0.5;

        if (gPlayers[i].y < -io->DisplaySize.y / 50 - 2 )
            gPlayers[i].y = 0.5;
        if (gPlayers[i].y > 1)
            gPlayers[i].y = -io->DisplaySize.y / 50 - 0.5;
    }
}
//Displays debug informations
void playerDebug(App* app)
{
    igText("DeltaTime: %f", app->deltaTime);
    for (int i = 0; i < 2; i++)
    {
        
        igText("Player %d", i + 1);
        igText("   X: %f", gPlayers[i].x);
        igText("   Y: %f", gPlayers[i].y);
        igText("   Momentum X: %f", gPlayers[i].momentumX);
        igText("   Momentum Y: %f", gPlayers[i].momentumY);
        igText("   Speed: %f", sqrt(pow(gPlayers[i].momentumX, 2.0f) + pow(gPlayers[i].momentumY, 2.0f)));
        igText("   Angle: %f", gPlayers[i].angle);
        igText("----------");
    }
}
//Unites all of the above functions
void playerScript(App* app)
{
    drawPlayer(app);
    playerControls(app);
    playerFrictions(app);
    playerMovement(app);
    bulletUpdate(app);
    playerOOB(app);
    bulletDebug();
    playerDebug(app);
}