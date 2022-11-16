#include "player.h"
#include "../entities/bullet.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define PI 3.14159276
#define maxBulletCount 256
#define bulletLifetime 5

pStruct player;
struct pBullet bullet [maxBulletCount];

//Initializes the player's position
void playerInit(App* app)
{
    player.x = 10;
    player.y = -7;
    for (int i = 0; i <= maxBulletCount; i++)
    {
        bullet[i].isActive = 0;
        bullet[i].timeBeforeDeath = bulletLifetime;
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

    for (int i = 0; i < 6; ++i)
    {
        float2 newPoint = points[i];
        float2 temp = newPoint;
        float2 xy = {0, 0};
        newPoint.x = rotatePoint(temp, xy, player.angle).x + player.x;
        newPoint.y = rotatePoint(temp, xy, player.angle).y + player.y;

        cvPathLineTo(newPoint.x, newPoint.y);
    }
    cvPathStroke(CV_COL32_WHITE, 1);
    cvAddPoint(player.x, player.y, CV_COL32(255,0,0,255));
}

void playerTeleport(App* app)
{
    ImGuiIO* io = igGetIO();
    player.x = rand() % ((int) io->DisplaySize.x / 50);
    player.y = -rand() % ((int) io->DisplaySize.y / 50);
}

bool fireBullet()
{
    float oldestBullet = bulletLifetime;
    int oldestBulletIndex = 0;
    for (int i = 0; i <= maxBulletCount; i++)
    {
        if (bullet[i].isActive == 0)
        {
            bullet[i].isActive = 1;
            bullet[i].x = player.x;
            bullet[i].y = player.y;
            bullet[i].angle = player.angle;
            return 0;
        }
        if (bullet[i].timeBeforeDeath < oldestBullet)
        {
            oldestBullet = bullet[i].timeBeforeDeath;
            oldestBulletIndex = i;
        }
    }
    bullet[oldestBulletIndex].x = player.x;
    bullet[oldestBulletIndex].y = player.y;
    bullet[oldestBulletIndex].timeBeforeDeath = 3;
    bullet[oldestBulletIndex].angle = player.angle;
    return 0;
}
void bulletUpdate(App* app)
{
    ImGuiIO* io = igGetIO();
    for (int i = 0; i <= maxBulletCount; i++)
    {
        if (bullet[i].isActive == 1)
        {
            bullet[i].x += cosf(bullet[i].angle + (PI / 2)) * app -> deltaTime * 10;
            bullet[i].y += sinf(bullet[i].angle + (PI / 2)) * app -> deltaTime * 10;
            bullet[i].timeBeforeDeath -= app -> deltaTime;
            cvAddPoint(bullet[i].x, bullet[i].y, CV_COL32_WHITE);
        }
        if (bullet[i].timeBeforeDeath <= 0)
        {
            bullet[i].timeBeforeDeath = bulletLifetime;
            bullet[i].isActive = 0;
        }

        if (bullet[i].x > io->DisplaySize.x / 50 + 1)
            bullet[i].x = -0.5;
        if (bullet[i].x < -1)
            bullet[i].x = io->DisplaySize.x / 50 + 0.5;

        if (bullet[i].y < -io->DisplaySize.y / 50 - 2 )
            bullet[i].y = 0.5;
        if (bullet[i].y > 1)
            bullet[i].y = -io->DisplaySize.y / 50 - 0.5;
    }
}
void bulletDebug()
{
    int bulletCount = 0;
    for (int i = 0; i < maxBulletCount; i++)
    {
        if (bullet[i].isActive == true)
        {
            bulletCount ++;
        }
    }
    igText("Drawn Bullets: %d | Max: %d", bulletCount, maxBulletCount);
}


//Checks for input and prepare for movement
void playerControls(App* app)
{
    float velocity = sqrt(pow(player.momentumX, 2.0f) + pow(player.momentumY, 2.0f));
    float direction = atan2f(player.momentumY, player.momentumX);
    //Controls
        if (igIsKeyDown(ImGuiKey_D) || igIsKeyDown(ImGuiKey_LeftArrow))
        {
            player.angle += (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_G) || igIsKeyDown(ImGuiKey_RightArrow))
        {
            player.angle -= (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_R) || igIsKeyDown(ImGuiKey_UpArrow))
        {   
            player.momentumX += (sin(-player.angle) * 0.25f);
            player.momentumY += (cos(-player.angle) * 0.25f);
        }

        if (igIsKeyReleased(ImGuiKey_K))
        {
            playerTeleport(app);
        }
        if (igIsKeyReleased(ImGuiKey_N))
        {
            fireBullet();
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
    player.x += player.momentumX * app->deltaTime;
    player.y += player.momentumY * app->deltaTime;
}
//Friction processing
void playerFrictions(App* app)
{
    //Friction
    player.momentumX *= 0.98f;// * app->deltaTime;
    player.momentumY *= 0.98f;// * app->deltaTime;
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
    igText("   X: %f", player.x);
    igText("   Y: %f", player.y);
    igText("   Momentum X: %f", player.momentumX);
    igText("   Momentum Y: %f", player.momentumY);
    igText("   Speed: %f", sqrt(pow(player.momentumX, 2.0f) + pow(player.momentumY, 2.0f)));
    igText("   Angle: %f", player.angle);
    igText("----------", player.angle);
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
    playerDebug(app);
    bulletDebug();
}