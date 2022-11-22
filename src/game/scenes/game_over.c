void displayGameOver(App* app)
{
    ImGuiIO* io = igGetIO();
    cvAddTexture(io->DisplaySize.x/50/2,-io->DisplaySize.y/50/2, app->graphics.textures.gameOver);
    drawHUDScore(app);
    if (igIsKeyPressed(ImGuiKey_Escape, 0))
    {
        playerInit(app);
        app->scene = 0;
    }

}