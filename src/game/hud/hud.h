#ifndef HUD_H
#define	HUD_H
#include "../../app.h"

void	drawHUDLivesLeft(Player *player, bool onTheLeft);
void	drawHUDScore(Player *player, bool onTheLeft);
void	drawHUDLevel(App* app);

#endif