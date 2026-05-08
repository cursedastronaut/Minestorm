#ifndef BULLET_H
#define BULLET_H
#include <stdbool.h>
#include <toolbox.h>
#ifndef PLAYER_H
#include "player/player.h"
#endif

typedef struct Mine Mine;

typedef struct Bullet
{
	float2	pos;
	float	angle;
	float	timeBeforeDeath;
	float2	momentum;
	int		isActive;
	int		opacity;
	Player*	ownerPlayer;
	
} Bullet;

void	bulletUpdate(App* app, Player **player, uint8_t playerAmount);
void	bulletCreate(Player *owner);
void	bulletInit(Bullet *bullet);
void	bulletMineCollision(Bullet *bullet, Mine *mine, App *app, float2 mineBox[4]);

#endif