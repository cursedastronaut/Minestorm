

void displayGameOver(App* app)
{
    ImGuiIO* io = igGetIO();
    cvAddTexture(io->DisplaySize.x/50/2,-io->DisplaySize.y/50/2, app->graphics.textures.gameOver);
    switch (app->twoPlayers)
    {
    case false:
        cvAddFormattedText(2,-2, CV_COL32_WHITE, "Best Score: %d", app->bestScoreSingleplayer);
        break;
    
    case true:
        cvAddFormattedText(2,-2, CV_COL32_WHITE, "Best Score: %d", app->bestScoreMultiplayer[0]);
        cvAddFormattedText(6,-2, CV_COL32_WHITE, "Best Score: %d", app->bestScoreMultiplayer[1]);
        break;
    }
    
    drawHUDScore(app);
    if (igIsKeyPressed(ImGuiKey_Escape, 0))
    {
        playerInit(app);
        app->paused = false;
        app->twoPlayers = false;
        app->scene = 0;
        chanceMineFloating = 100;
        chanceMineFireball = 0;
        chanceMineMagnetic = -20;
        chanceMineFiremag  = -40;
        level = 0;
        app->gameinit = false;
    }

}