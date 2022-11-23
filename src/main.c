#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <canvas.h>

#include "app.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    // In playback mode copy data to pOutput. In capture mode read data from pInput. In full-duplex mode, both
    // pOutput and pInput will be valid and you can move data from pInput into pOutput. Never process more than
    // frameCount frames.
}

int main()
{
    // Init glfw
    GLFWwindow* window = NULL;
    {
        if (glfwInit() != GLFW_TRUE)
        {
            const char* error; glfwGetError(&error);
            fprintf(stderr, "glfwInit() failed: %s\n", error);
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window = glfwCreateWindow(1000, 800, "Minestorm (g.martineaux, m.akkari)", NULL, NULL);
        if (window == NULL)
        {
            const char* error; glfwGetError(&error);
            fprintf(stderr, "glfwCreateWindow() failed: %s\n", error);
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
    }
    


    // Init canvas library
    CanvasConfig config = cvGetDefaultConfig();
    cvInit(window, config);

    // Init our app
    App app = {0};
    appInit(&app);

    // Main loop
    while (glfwWindowShouldClose(window) == GLFW_FALSE && app.shutdown == false)
    {
        // Begin
        glfwPollEvents();
        cvNewFrame();
        appUpdate(&app);
        
        // End
        cvEndFrame();
        app.animtime ++;
        if (app.animtime > 256)
            app.animtime = 1;
        glfwSwapBuffers(window);
    }

    // Shutdown
    appShutdown(&app);
    ma_engine_uninit(&app.engine);
    cvShutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
