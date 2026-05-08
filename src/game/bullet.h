#include <stdbool.h>
#include <toolbox.h>
#include "player/player.h"


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

extern Bullet gBullets [MAX_BULLET_COUNT];

void	bulletUpdate(App* app, Player **player, uint8_t playerAmount);