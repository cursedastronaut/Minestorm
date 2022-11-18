#include <stdlib.h>
#define HORIZONTAL_STATICEFFECT_BLOCKS 256
#define VERTICAL_STATICEFFECT_BLOCKS 96


void staticDisplay(App* app)
{
    if (app->graphics.show_static == true)
    {
        ImGuiIO* io = igGetIO();
        float2 points[5] = {
            {0.0f,                                                              0.0f},
            {(io->DisplaySize.x / 50.f) / HORIZONTAL_STATICEFFECT_BLOCKS,       0.0f},
            {(io->DisplaySize.x / 50.f) / HORIZONTAL_STATICEFFECT_BLOCKS,       - (io->DisplaySize.y / 50.f) / VERTICAL_STATICEFFECT_BLOCKS},
            {0.0f,                                                              - (io->DisplaySize.y / 50.f) / VERTICAL_STATICEFFECT_BLOCKS},
        };
        for (int y = 0; y != -VERTICAL_STATICEFFECT_BLOCKS - 1; y--)
        {
            for (int x = 0; x != HORIZONTAL_STATICEFFECT_BLOCKS + 1; x++)
            {
            for (int i = 0; i != 4; i++)
                {
                    cvPathLineTo(   points[i+1].x + (io->DisplaySize.x / 50.f) / HORIZONTAL_STATICEFFECT_BLOCKS * x,
                                    points[i+1].y + (io->DisplaySize.y / 50.f) / VERTICAL_STATICEFFECT_BLOCKS * y
                                );
                }
                int intensity = rand() % (255 - 128 + 1) + 128;
                cvPathFill(CV_COL32(intensity, intensity, intensity, 16)); 
                cvPathStroke(CV_COL32(0,0,0,0), 1);
            }
        }
    }
}