void displayGameOver(App* app)
{
    ImGuiIO* io = igGetIO();
    cvAddTexture(io->DisplaySize.x/50/2,-io->DisplaySize.y/50/2, app->graphics.textures.gameOver);
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