#include "projectile.h"

#include <canvas.h>
#include <stdio.h>
#include <stdlib.h>

void updateProjectileState(Projectile* p, double deltaTime, float screenWidth, float screenHeight)
{
    // Movement
    p->pos = translatePoint2(p->pos, p->speed);

    // Reset position if outside the screen
    if (p->pos.x > screenWidth + PROJECTILE_OUTSIDE_SCREEN_HORIZONTAL_DISTANCE)
        p->pos.x = 0 - PROJECTILE_OUTSIDE_SCREEN_HORIZONTAL_DISTANCE;
    if (p->pos.x < 0 - PROJECTILE_OUTSIDE_SCREEN_HORIZONTAL_DISTANCE)
        p->pos.x = screenWidth + PROJECTILE_OUTSIDE_SCREEN_HORIZONTAL_DISTANCE;
    if (p->pos.y > screenHeight + PROJECTILE_OUTSIDE_SCREEN_VERTICAL_DISTANCE)
        p->pos.y = 0 - PROJECTILE_OUTSIDE_SCREEN_VERTICAL_DISTANCE;
    if (p->pos.y < 0 - PROJECTILE_OUTSIDE_SCREEN_VERTICAL_DISTANCE)
        p->pos.y = screenHeight + PROJECTILE_OUTSIDE_SCREEN_VERTICAL_DISTANCE;

    // LifeTime
    p->timeLeft -= deltaTime;

    // CollisionBox
    p->box.point.p = p->pos;
}

void drawProjectile(Projectile* p)
{
    cvAddPoint(p->pos.x, p->pos.y, CV_COL32_WHITE);
}
