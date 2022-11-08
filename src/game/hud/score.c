#include <string.h>

//Draws the score on the HUD.
void drawHUDScore(App* app)
{
    char output[15]; //Max score can only contain 8 numbers. (99999999)
    sprintf(output, "Score: %d", app->HUD.p1_score);
    //app->p1_score++;
    ImGuiIO* io = igGetIO();
    cvAddText(
        (io->DisplaySize.x/50) - (strlen(output)) * 0.3 , //Formula to move text when there are more numbers
        0, CV_COL32_WHITE, output);
}