#pragma once
#ifndef		PLAYER_H
# define	PLAYER_H
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <toolbox.h>
# include	"../tinkering.h"

typedef struct App App;

struct playerControls
{
	ImGuiKey_ rotateRight;
	ImGuiKey_ rotateLeft;
	ImGuiKey_ rotateRightAlt;
	ImGuiKey_ rotateLeftAlt;
	ImGuiKey_ teleport;
	ImGuiKey_ teleportAlt;
	ImGuiKey_ forward;
	ImGuiKey_ forwardAlt;
	ImGuiKey_ fire;
};


typedef struct Player
{
	float2			pos;
	float			angle;
	float			momentumX;
	float			momentumY;
	int				score;
	int				lives;
	float			invincibility;
	unsigned int	color;
	App				*app;
	struct playerControls	controls;
} Player;

extern const float2 shapePlayer[6];

void	playerInit(App* app, Player* player, bool playerNumber);
void	playerScript(Player* app);
void	killPlayer(Player *player);

#endif