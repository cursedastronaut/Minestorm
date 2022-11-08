void drawHUDLivesLeft(App* app)
{
    cvAddFormattedText(3,-3, CV_COL32_WHITE, "P1 Li%s: %d", app->HUD.p1_lives > 1 ? "ves" : "fe", app->HUD.p1_lives);
}