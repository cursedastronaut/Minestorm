#pragma once
#include "entities.h"
#include <stdlib.h>
#include "../tinkering.h"
#include "../player/player.c"
struct entMF fmine [MINE_MAX];   //Choosing the amount of mines (see tinkering.h)
int level = 7;
void mineInit()
{
    ImGuiIO* io = igGetIO();
    for(int i = 0; i < MINE_AMOUNT_INITIAL ; i++) //Looping through all the mines
    {
        fmine[i].angle = rand() % 360;                                  //Sets a random angle
        fmine[i].angle *= PI/180;                                  //Sets a random angle
        fmine[i].size = 3;
        // fmine[i].type = floor(fmin(i * level * 0.1f, 4));
        fmine[i].type = 1;
        fmine[i].x = rand() % ((int)igGetIO()->DisplaySize.x / 50);     //Sets a random position on the X axis (within the window's limits)
        fmine[i].y = -rand() % ((int)igGetIO()->DisplaySize.y / 50);    //Sets a random position on the Y axis (within the window's limits)
        fmine[i].momentumX = cosf(fmine[i].angle) * 0.1;                //Sets the momentum variables so that it goes
        fmine[i].momentumY = sinf(fmine[i].angle) * 0.1;                //in the direction of its angle.
        fmine[i].isActive = true;
    }
}
void killMineFloating(int index)
{
    if (fmine[index].size == 1)
    {
        fmine[index].isActive = false;
    }
    else
    {
        fmine[index].size --;
        for (int i = 0; i < MINE_MAX; i++)
        {
            if (fmine[i].isActive == false)
            {
                fmine[i].angle = fmine[index].angle;
                fmine[i].size = fmine[index].size;
                fmine[i].type = fmine[index].type;
                fmine[i].x = fmine[index].x - 0.3;
                fmine[i].y = fmine[index].y - 0.3;
                fmine[i].momentumX = cosf(fmine[i].angle) * 0.1;                //Sets the momentum variables so that it goes
                fmine[i].momentumY = sinf(fmine[i].angle) * 0.1;                //in the direction of its angle.
                fmine[i].isActive = true;
                break;
            }
        }
        fmine[index].angle += PI;
        fmine[index].momentumX = cosf(fmine[index].angle) * 0.1;
        fmine[index].momentumY = sinf(fmine[index].angle) * 0.1;
    }
}
void drawMineFloating(entMF currentMine)
{
    //Shape
    int verticeAmount = 8;
    float2 pointsFloat[6] = {
        { 0.1f * cosf(PI / 2), 0.1f * sinf(PI / 2)},            
        { 0.3f * cosf(PI / 6), 0.3f * sinf(PI / 6)},
        { 0.1f * cosf(-PI / 6), 0.1f * sinf(-PI / 6)},
        { 0.3f * cosf(-PI / 2), 0.3f * sinf(-PI / 2)},
        { 0.1f * cosf(-5 * PI / 6), 0.1f * sinf(-5 * PI / 6)},
        { 0.3f * cosf((5 * PI) / 6), 0.3f * sinf((5 * PI) / 6)}
    };
    float2 pointsFire[8] = {
        { 0.15f * cosf(PI / 2), 0.15f * sinf(PI / 2)},
        { 0.3f * cosf(PI / 4), 0.3f * sinf(PI / 4)},
        { 0.15f * cosf(0), 0.15f * sinf(0)},
        { 0.3f * cosf(PI / 4), 0.3f * -sinf(PI / 4)},
        { 0.15f * cosf(PI / 2), 0.15f * -sinf(PI / 2)},
        { 0.3f * -cosf(PI / 4), 0.3f * -sinf(PI / 4)},
        { 0.15f * cosf(PI), 0.15f * sinf(PI)},
        { 0.3f * -cosf(PI / 4), 0.3f * sinf(PI / 4)}
    };
    float2 pointsMagnetic[8] = {
        { 0.1f * cosf(PI / 2), 0.1f * sinf(PI / 2)},
        { 0.25f * cosf(PI / 4), 0.25f * sinf(PI / 4)},
        { 0.1f * cosf(0), 0.1f * sinf(0)},
        { 0.25f * cosf(PI / 4), 0.25f * -sinf(PI / 4)},
        { 0.1f * cosf(PI / 2), 0.1f * -sinf(PI / 2)},
        { 0.25f * -cosf(PI / 4), 0.25f * -sinf(PI / 4)},
        { 0.1f * cosf(PI), 0.1f * sinf(PI)},
        { 0.25f * -cosf(PI / 4), 0.25f * sinf(PI / 4)}
    };
    float2 pointsFiremag[8] = {
        { 0.3f * cosf(PI / 2), 0.3f * sinf(PI / 2)},
        { 0.2f * cosf(PI / 2), 0.2f * sinf(PI / 2)},
        { 0.3f * cosf(0), 0.3f * sinf(0)},
        { 0.2f * cosf(0), 0.2f * sinf(0)},
        { 0.3f * cosf(PI / 2), 0.3f * -sinf(PI / 2)},
        { 0.2f * cosf(PI / 2), 0.2f * -sinf(PI / 2)},
        { 0.3f * cosf(PI), 0.3f * sinf(PI)},
        { 0.2f * cosf(PI), 0.2f * sinf(PI)}
    };
    if (currentMine.isActive == true)
    {
        for (int j = 0; j < verticeAmount; ++j)     //Looping through the points
        {
            float2 newPoint;
            switch (currentMine.type)
            {
                case 0: newPoint = pointsFloat[j];
                verticeAmount = 6;
                break;
                case 1: newPoint = pointsFire[j];
                break;
                case 2: newPoint = pointsMagnetic[j];
                break;
                case 3: newPoint = pointsFiremag[j];
                break;
            }
            newPoint.x *= currentMine.size;
            newPoint.y *= currentMine.size;
            newPoint.x += currentMine.x;
            newPoint.y += currentMine.y;

            cvPathLineTo(newPoint.x, newPoint.y); 
        }
        cvPathStroke(CV_COL32_WHITE, 1);
    }
}

void checkMinesIntegrity()
{
    int integrity = 0;
    for (int i = 0; i < MINE_MAX; i++)
    {
        integrity += fmine[i].isActive;
    }
    if (integrity == 0)
        cvAddText(3,-3, CV_COL32_WHITE , "YAAAAAAAAAAAAA");
}

void entityMineFloating(App* app)
{
    //Movement
    for (int i = 0; i < MINE_MAX; i++)
    {
        if (fmine[i].isActive == true)
        {
            drawMineFloating(fmine[i]);
            switch (fmine[i].type)
            {
            case 0 ... 1: //Floating Mine && Fireball Mine
                fmine[i].x += fmine[i].momentumX * app -> deltaTime * (4 - fmine[i].size) * 3; //Make it move.
                fmine[i].y += fmine[i].momentumY * app -> deltaTime * (4 - fmine[i].size) * 3;
                break;
            
            case 3 ... 4: //Magnetic Mine, Magnetic-Fireball Mine
                int tempX;  int tempY;
                tempX = gPlayers[0].x - fmine[i].x;
                tempY = gPlayers[0].y - fmine[i].y;
                fmine[i].momentumX += tempX * 0.01;
                fmine[i].momentumY += tempY * 0.01;
                fmine[i].momentumY *= 0.97;
                fmine[i].momentumX *= 0.97;
                fmine[i].x += fmine[i].momentumX * app -> deltaTime * (4 - fmine[i].size) * 0.98; //Make it move.
                fmine[i].y += fmine[i].momentumY * app -> deltaTime * (4 - fmine[i].size) * 0.98;

                break;

            default:
                break;
            }
            
            //Loop around borders
            ImGuiIO* io = igGetIO();
            if (fmine[i].x > io->DisplaySize.x / 50 + 1)
                fmine[i].x = -0.5;
            if (fmine[i].x < -1)
                fmine[i].x = io->DisplaySize.x / 50 + 0.5;

            if (fmine[i].y < -io->DisplaySize.y / 50 - 2 )
                fmine[i].y = 0.5;
            if (fmine[i].y > 1)
                fmine[i].y = -io->DisplaySize.y / 50 - 0.5;
            
            
            float2 mineBox[4] = 
            {
                { fmine[i].x + (0.4f * fmine[i].size), fmine[i].y + (0.4f * fmine[i].size) },
                { fmine[i].x + (0.4f * fmine[i].size), fmine[i].y + (-0.4f * fmine[i].size) },
                { fmine[i].x + (-0.4f * fmine[i].size), fmine[i].y + (-0.4f * fmine[i].size) },
                { fmine[i].x + (-0.4f * fmine[i].size), fmine[i].y + (0.4f * fmine[i].size) }
            };
            for (int p = 0; p < 2; p++)
            {
                if (gPlayers[p].invincibility <= 0)
                {
                    float2 collisionSquare[4] =
                    {
                        { -0.5f + gPlayers[p].x, 0.5f + gPlayers[p].y},
                        { 0.5f + gPlayers[p].x, 0.5f + gPlayers[p].y},
                        { 0.5f + gPlayers[p].x, -0.5f + gPlayers[p].y},
                        { -0.5f + gPlayers[p].x, -0.5f + gPlayers[p].y}
                    };
                    if (checkCollisionSquareSquare(mineBox, collisionSquare, app))
                    {
                        killPlayer(p);
                    }
                }
                
            }
            for (int b = 0; b < MAX_BULLET_COUNT; b++)
            {
                if (gBullets[b].isActive == true)
                {
                    int specialBonus;
                    switch (fmine[i].type)
                    {
                        case 0: specialBonus = 0; break;
                        case 1: specialBonus = 225; break;
                        case 2: specialBonus = 400; break;
                        case 3: specialBonus = 650; break;
                    }
                    float2 bulletSquare[4] =
                    {
                        { -0.2f + gBullets[b].x, 0.2f + gBullets[b].y},
                        { 0.2f + gBullets[b].x, 0.2f + gBullets[b].y},
                        { 0.2f + gBullets[b].x, -0.2f + gBullets[b].y},
                        { -0.2f + gBullets[b].x, -0.2f + gBullets[b].y}
                    };
                    if (checkCollisionSquareSquare(mineBox, bulletSquare, app))
                    {
                        gBullets[b].timeBeforeDeath = BULLET_LIFE_TIME;
                        gBullets[b].isActive = 0;                       //Killing the bullet.
                        switch(fmine[i].size)
                        {
                            case 1: gPlayers[gBullets[b].player].score += 200; break;
                            case 2: gPlayers[gBullets[b].player].score += 135; break;
                            case 3: gPlayers[gBullets[b].player].score += 100; break;
                        }
                        gPlayers[gBullets[b].player].score += specialBonus;
                        killMineFloating(i);
                    }   
                }
                
            }
                
        }
        
    }
    checkMinesIntegrity();
    //DEBUG
    if (igIsKeyReleased(ImGuiKey_M))
    {
        killMineFloating(0);
    }
}

//To do:
/*
Make the magnetic mine go to the nearest player
Make it detect when all the mines are dead
*/