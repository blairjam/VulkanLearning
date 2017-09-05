#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class HelloTriangle {
public:
    HelloTriangle();
    void run();

private:
    const int32_t WINDOW_WIDTH  = 800;
    const int32_t WINDOW_HEIGHT = 600;
    const char* WINDOW_TITLE    = "Vulkan";

    GLFWwindow* window;
    VkInstance instance;

    void initWindow();
    void initVulkan();
    void createInstance();
    void checkExtensions(uint32_t*, const char***);
    void mainLoop();
    void cleanup();
};
