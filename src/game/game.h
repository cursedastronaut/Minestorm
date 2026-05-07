#ifndef	GAME_H
#define	GAME_H

extern int level;

typedef struct App App;

void	gameInit(App* app);
void	displayGame(App* app);
void	processingGame(App* app);

#endif
