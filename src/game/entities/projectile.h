#pragma once

#include "collisionBox.h"

#include <vector2.h>

#define PROJECTILE_LIFE_TIME 2.5
#define PROJECTILE_DAMAGE 1
#define PROJECTILE_SPEED 10
#define PROJECTILE_OUTSIDE_SCREEN_HORIZONTAL_DISTANCE 2
#define PROJECTILE_OUTSIDE_SCREEN_VERTICAL_DISTANCE 2

typedef struct Projectile {
    Point2 pos;
    Vector2 speed;
    double timeLeft;

    CollisionBox box;
} Projectile;

void updateProjectileState(Projectile*, double deltaTime, float screenWidth, float screenHeight);
void drawProjectile(Projectile*);
