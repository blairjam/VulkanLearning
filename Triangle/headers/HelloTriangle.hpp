#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class HelloTriangle {
public:
    void run();

private:
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const char* WINDOW_TITLE = "Vulkan";
    
    GLFWwindow* window;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
};
