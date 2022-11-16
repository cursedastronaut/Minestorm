#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <canvas.h>

#include "app.h"

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
    cvShutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
