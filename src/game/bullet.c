#include "bullet.h"
#include "../mine/mine.h"
#include "../app.h"
#include <canvas.h>
#include <math.h>

void	bulletInit(Bullet *bullet)
{
	bullet->isActive = false;
	bullet->timeBeforeDeath = BULLET_LIFE_TIME;
}

static void bulletDraw(Bullet *bullet)
{
	cvAddPoint(bullet->pos.x, bullet->pos.y, CV_COL32(255,255,255,bullet->opacity));
}

static void	bulletMovement(Bullet *bullet)
{
	if (!bullet)
		return;
	bullet->pos.x += bullet->momentum.x;
	bullet->pos.y += bullet->momentum.y;
	ImGuiIO* io = igGetIO();
	//Making it loop with the borders
	if (bullet->pos.x > io->DisplaySize.x / 50 + 1)
		bullet->pos.x = -0.5;
	if (bullet->pos.x < -1)
		bullet->pos.x = io->DisplaySize.x / 50 + 0.5;

	if (bullet->pos.y < -io->DisplaySize.y / 50 - 2 )
		bullet->pos.y = 0.5;
	if (bullet->pos.y > 1)
		bullet->pos.y = -io->DisplaySize.y / 50 - 0.5;
}

static void bulletAging(Bullet *bullet, App *app)
{
	bullet->timeBeforeDeath -= app->deltaTime;

	//Gradually lowering the bullet's opacity until its death
	if (bullet->timeBeforeDeath <= 1.0f)
		bullet->opacity -= 255/60;
}

static void	bulletDestroy(Bullet *bullet)
{
	bullet->timeBeforeDeath = BULLET_LIFE_TIME;
	bullet->isActive = false; 
}

static void	bulletPlayerCollision(Bullet *bullet, Player *player, float2 bulletSquare[4])
{
	float2 playerSquare[4] =
	{
		{ -0.5f + player->pos.x, +0.5f + player->pos.y},
		{ +0.5f + player->pos.x, +0.5f + player->pos.y},
		{ +0.5f + player->pos.x, -0.5f + player->pos.y},
		{ -0.5f + player->pos.x, -0.5f + player->pos.y}
	};
	if (player->invincibility <= 0 && checkCollisionSquareSquare(bulletSquare, playerSquare, player->app->graphics.show_collisionbox))
	{
		printf("player->app->graphics.show_collisionbox: %s\n", player->app->graphics.show_collisionbox ? "true" : "false");
		bulletDestroy(bullet);
		--player->lives;
		player->invincibility = 5.0f;
	}
}

void	bulletMineCollision(Bullet *bullet, Mine *mine, App *app, float2 mineBox[4])
{
	if (bullet->isActive == true)
	{
		int specialBonus;
		switch (mine->type)
		{
			case 0: specialBonus = 0;	break;
			case 1: specialBonus = 225;	break;
			case 2: specialBonus = 400;	break;
			case 3: specialBonus = 650;	break;
			case 4: specialBonus = 0;	break;
		}
		float2 bulletSquare[4] =
		{
			{ -0.2f + bullet->pos.x, +0.2f + bullet->pos.y},
			{ +0.2f + bullet->pos.x, +0.2f + bullet->pos.y},
			{ +0.2f + bullet->pos.x, -0.2f + bullet->pos.y},
			{ -0.2f + bullet->pos.x, -0.2f + bullet->pos.y}
		};
		if (checkCollisionSquareSquare(mineBox, bulletSquare, app))
		{
			//ma_engine_play_sound(&app->engine, "assets/audio/mine-death.mp3", NULL);
			bullet->timeBeforeDeath = BULLET_LIFE_TIME;
			bullet->isActive = 0;                       //Killing the bullet.
			switch(mine->size)
			{
				case 1: bullet->ownerPlayer->score += 200;
				if (mine->type == 4)
					bullet->ownerPlayer->score -= 90;
				break;
				case 2: bullet->ownerPlayer->score += 135; break;
				case 3: bullet->ownerPlayer->score += 100; break;
			}
			bullet->ownerPlayer->score += specialBonus;
			killMineFloating(mine, bullet->ownerPlayer);
		}   
	}
}

void	bulletCreate(Player *owner)
{
	float	oldestBullet = BULLET_LIFE_TIME;
	int		oldestBulletIndex = -1;

	Bullet	*bullets = owner->app->bullets;
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (!bullets[i].isActive)
		{
			bullets[i].isActive = true;
			bullets[i].angle = owner->angle;
			bullets[i].pos.x = rotatePoint( (float2){0.f,0.8f},
				(float2){0.f, 0.f}, owner->angle).x + owner->pos.x; //Bullet's X position is set to Player's X position
			bullets[i].pos.y = rotatePoint( (float2){0.f,0.8f},
				(float2){0.f, 0.f}, owner->angle).y + owner->pos.y; //Bullet's Y position is set to Player's Y position
			bullets[i].opacity = 255;
			bullets[i].ownerPlayer = owner;
			bullets[i].momentum.x = (sinf(-owner->angle) * 0.27f);
			bullets[i].momentum.y = (cosf(-owner->angle) * 0.27f);
			return ;
		}
		if (bullets[i].timeBeforeDeath < oldestBullet)
		{
			oldestBullet = bullets[i].timeBeforeDeath;
			oldestBulletIndex = i;
		}
	}

	//Replace the oldest bullet if no deactivated bullet could be found
	if (oldestBulletIndex != -1)
	{
		bullets[oldestBulletIndex].angle = owner->angle;
		bullets[oldestBulletIndex].pos.x = rotatePoint( (float2){0.f,0.8f},
			(float2){0.f, 0.f}, owner->angle).x + owner->pos.x; //Bullet's X position is set to Player's X position
		bullets[oldestBulletIndex].pos.y = rotatePoint( (float2){0.f,0.8f},
			(float2){0.f, 0.f}, owner->angle).y + owner->pos.y; //Bullet's Y position is set to Player's Y position
		bullets[oldestBulletIndex].opacity = 255;
		bullets[oldestBulletIndex].ownerPlayer = owner;
		bullets[oldestBulletIndex].momentum.x = (sinf(-owner->angle) * 0.27f);
		bullets[oldestBulletIndex].momentum.y = (cosf(-owner->angle) * 0.27f);
	}
}

void bulletUpdate(App* app, Player **player, uint8_t playerAmount)
{
	for (unsigned int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (!app->bullets[i].isActive)
			continue;
		bulletMovement(&app->bullets[i]);
		bulletDraw(&app->bullets[i]);
		bulletAging(&app->bullets[i], app);

		if (app->bullets[i].timeBeforeDeath <= 0)
			bulletDestroy(&app->bullets[i]);

		float2 bulletSquare[4] =
		{
			{ -0.2f + app->bullets[i].pos.x, +0.2f + app->bullets[i].pos.y},
			{ +0.2f + app->bullets[i].pos.x, +0.2f + app->bullets[i].pos.y},
			{ +0.2f + app->bullets[i].pos.x, -0.2f + app->bullets[i].pos.y},
			{ -0.2f + app->bullets[i].pos.x, -0.2f + app->bullets[i].pos.y}
		};
		
		for (int j = 0; j < playerAmount; ++j)
			bulletPlayerCollision(&app->bullets[i], player[j], bulletSquare);
	}
}