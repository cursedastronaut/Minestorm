#pragma once
#include "player.h"
#include "../entities/bullet.h"
#include "../../geo/collision.c"
#include <stdlib.h>
#include <time.h>
#include "../tinkering.h"
#include <unistd.h>


Player gPlayers [MAX_AMOUNT_OF_PLAYERS];
Bullet gBullets [MAX_BULLET_COUNT];

//Initializes the player's position
void playerInit(App* app)
{
    //Sets the positions
    gPlayers[0].x = 12.5;       gPlayers[0].y = -7;
    if (app->twoPlayers == true)
    {
        gPlayers[1].x = 7.5;    gPlayers[1].y = -7;
    }
    else
    {
        gPlayers[1].x = 0;    gPlayers[1].y = 2;
    }

    for (int i = 0; i < MAX_BULLET_COUNT; i++) //Loops through the bullets
    {
        gBullets[i].isActive = 0; //Deactivating the bullets (just in case)
        gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME; //See tinkering.h
    }
    for (int i = 0; i<2 ; i++)
    {
        gPlayers[i].score = 0; //Initial score
        gPlayers[i].lives = 3;
        gPlayers[i].momentumX = 0;
        gPlayers[i].momentumY = 0;
        gPlayers[i].angle = 0;
        gPlayers[i].invincibility = 5.0f;
    }
}
//Draws the player to the screen
bool drawPlayer(App* app)
{
    float2 points[6] = { //Shape
        { 0.0f, 0.5f },
        { 0.5f, -0.3f },
        { 0.35f, -0.3f },
        { 0.0f, -0.5f },
        { -0.35f, -0.3f },
        { -0.5f, -0.3f },
    };
    for (int j = 0; j < 2; j++) //Looping through the players. j is the player index variable.
    {
        if (gPlayers[j].invincibility > 0)
        {
            if (app->animtime % 4 == 0)
            {}
            else
            {return true;}
        }
        for (int i = 0; i < 6; ++i) // Looping through the points making the shape.
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
    float2 staticSquare[4] = 
    {
        { 8, -7 },
        { 11, -7 },
        { 11, -10 },
        { 8, -10 }
    };
    float2 collisionSquare[4] =
    {
        { -0.5f + gPlayers[0].x, 0.5f + gPlayers[0].y},
        { 0.5f + gPlayers[0].x, 0.5f + gPlayers[0].y},
        { 0.5f + gPlayers[0].x, -0.5f + gPlayers[0].y},
        { -0.5f + gPlayers[0].x, -0.5f + gPlayers[0].y}
    };
}
//Teleports the player
void playerTeleport(App* app, int p)
{
    ImGuiIO* io = igGetIO();
    gPlayers[p].x = rand() % ((int) io->DisplaySize.x / 50);  //Moves the player with the index p to a
    gPlayers[p].y = -rand() % ((int) io->DisplaySize.y / 50); //random X and Y position within window limits.
}
//Fires a bullet
bool fireBullet(int p)
{
    float oldestBullet = BULLET_LIFE_TIME;
    int oldestBulletIndex = -1;
    for (int i = 0; i < MAX_BULLET_COUNT; i++)
    {
        if (gBullets[i].isActive == 0)
        {
            gBullets[i].isActive = 1;               //Bullet is now active.
            gBullets[i].angle = gPlayers[p].angle;  //Bullet's angle is set to Player's angle
            gBullets[i].x = rotatePoint( (float2){0.f,0.8f},
                (float2){0.f, 0.f}, gPlayers[p].angle).x + gPlayers[p].x;          //Bullet's X position is set to Player's X position
            gBullets[i].y = rotatePoint( (float2){0.f,0.8f},
                (float2){0.f, 0.f}, gPlayers[p].angle).y + gPlayers[p].y;          //Bullet's Y position is set to Player's Y position
            gBullets[i].opacity = 255;              //Bullet's opacity is set to max.
            gBullets[i].player = p;                 //Bullet's owner is the player who fired it.
            gBullets[i].momentumX = (sin(-gPlayers[p].angle) * 0.27f);
            gBullets[i].momentumY = (cos(-gPlayers[p].angle) * 0.27f);
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
            gBullets[i].x += gBullets[i].momentumX;  //cosf(gBullets[i].angle + (PI / 2)) * app -> deltaTime * 50; //Moves the bullet according
            gBullets[i].y += gBullets[i].momentumY;  //sinf(gBullets[i].angle + (PI / 2)) * app -> deltaTime * 50; //to its firing angle.
            gBullets[i].timeBeforeDeath -= app -> deltaTime;    //Lowering its lifetime.
            cvAddPoint(gBullets[i].x, gBullets[i].y, CV_COL32(255,255,255,gBullets[i].opacity)); //Drawing the bullet

            if (gBullets[i].timeBeforeDeath <= 1.0) //Gradually lowering the opacity
            {                                       //of the bullet before it dies.
                gBullets[i].opacity -= 255/60;
            }

            if (gBullets[i].timeBeforeDeath <= 0)
            {
                gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME;
                gBullets[i].isActive = 0;                       //Killing the bullet.
            }
            float2 bulletSquare[4] =
            {
                { -0.2f + gBullets[i].x, 0.2f + gBullets[i].y},
                { 0.2f + gBullets[i].x, 0.2f + gBullets[i].y},
                { 0.2f + gBullets[i].x, -0.2f + gBullets[i].y},
                { -0.2f + gBullets[i].x, -0.2f + gBullets[i].y}
            };
            float2 playerSquare[4] =
            {
                { -0.5f + gPlayers[0].x, 0.5f + gPlayers[0].y},
                { 0.5f + gPlayers[0].x, 0.5f + gPlayers[0].y},
                { 0.5f + gPlayers[0].x, -0.5f + gPlayers[0].y},
                { -0.5f + gPlayers[0].x, -0.5f + gPlayers[0].y}
            };
            if (checkCollisionSquareSquare(bulletSquare, playerSquare, app))
            {
                gBullets[i].timeBeforeDeath = BULLET_LIFE_TIME;
                gBullets[i].isActive = 0;                       //Killing the bullet.
                gPlayers[0].lives --;
            }

            //Making it loop with the borders
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

void killPlayer(int index)
{
    gPlayers[index].invincibility = 5.0;
    gPlayers[index].lives--;
}

void playerInvincibility(App* app)
{
    for (int index = 0; index < 2; index++)
    {
        if (gPlayers[index].invincibility > 0.0f)
        {
            gPlayers[index].invincibility -= app->deltaTime;
        }
    }
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

        if (igIsKeyReleased(ImGuiKey_T) || igIsKeyReleased(ImGuiKey_E))
        {
            playerTeleport(app,0);
        }
        if (igIsKeyReleased(ImGuiKey_F))
        {
            fireBullet(0);
        }
    
    //PLAYER 2
    if (app->twoPlayers == true)
    {
        if (igIsKeyDown(ImGuiKey_Keypad4) || igIsKeyDown(ImGuiKey_J))
        {
            gPlayers[1].angle += (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_Keypad6) ||igIsKeyDown(ImGuiKey_L))
        {
            gPlayers[1].angle -= (480.0f * PI / 360.0f) * app->deltaTime;
        }
        if (igIsKeyDown(ImGuiKey_Keypad8) || igIsKeyDown(ImGuiKey_I))
        {   
            gPlayers[1].momentumX += (sin(-gPlayers[1].angle) * 0.25f);
            gPlayers[1].momentumY += (cos(-gPlayers[1].angle) * 0.25f);
        }
        
        if (igIsKeyReleased(ImGuiKey_K))
        {
            playerTeleport(app,1);
        }
        if (igIsKeyReleased(ImGuiKey_U) || igIsKeyReleased(ImGuiKey_O))
        {
            fireBullet(1);
        }
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
        igText("   Inv.Time : %f", gPlayers[i].invincibility);
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
    playerInvincibility(app);
    bulletDebug();
    playerDebug(app);
}