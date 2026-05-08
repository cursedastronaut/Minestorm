#ifndef SCENES_H
#define SCENES_H

void displayMainMenu(App* app);
void processingMainMenu(App* app);
void displayGameOver(App* app);

enum sceneNames {
	SCENE_MAINMENU,
	SCENE_GAME,
	SCENE_GAMEOVER
};

#endif