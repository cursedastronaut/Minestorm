#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <canvas.h>
#include "../../app.h"
#include "../../game/game.h"
void drawHUDLevel(App* app)
{
    cvAddFormattedText( igGetIO()->DisplaySize.x/50/2 ,-1, CV_COL32_WHITE, "Level: %d", level);
}