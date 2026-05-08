#ifndef MINE_H
#define MINE_H
#include <toolbox.h>
#include <stdbool.h>

typedef struct App App;
typedef struct Player Player;

extern const float2 pointsFireball[8];
extern const float2 pointsFire[8];
extern const float2 pointsFloat[6];
extern const float2 pointsFiremag[8];
extern const float2 pointsMagnetic[8];

extern int chanceMineFloating;
extern int chanceMineFireball;
extern int chanceMineMagnetic;
extern int chanceMineFiremag;

typedef enum mineType
{
	MT_MineFloating,
	MT_MineFire,
	MT_MineMagnetic,
	MT_MineFiremag,
	MT_MineFireball,
}	mineType;

typedef struct Mine
{
	mineType		type;
	float2			pos;
	float			angle;
	float2			momentum;
	int				size;
	bool			isActive;
} Mine;

void entityType();
void mineInit(Mine *mine);
//Returns "true" on all mines dead.
bool	mineUpdate(Mine *mine, App *app, Player *player);
void	drawMine(Mine *currentMine);

void killMineFloating(Mine *mine, Player *player);


#endif