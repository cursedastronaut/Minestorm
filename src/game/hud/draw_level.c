#include "../entities/mine.c"
void drawHUDLevel(App* app)
{
    cvAddFormattedText( igGetIO()->DisplaySize.x/50/2 ,-1, CV_COL32_WHITE, "Level: %d", level);
}