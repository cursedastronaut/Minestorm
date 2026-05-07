#include <stdbool.h>

typedef struct Bullet
{
	float2	pos;
	float	angle;
	float	timeBeforeDeath;
	float2	momentum;
	int		isActive;
	int		opacity;
	bool	ownerPlayer;
} Bullet;