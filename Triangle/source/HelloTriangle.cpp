#include "HelloTriangle.hpp"

void HelloTriangle::run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void HelloTriangle::initWindow()
{
    glfwInit();

    // Tell glfw not to create an OpenGL context.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Disable window resizing.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
}

void HelloTriangle::initVulkan()
{
}

void HelloTriangle::mainLoop()
{
    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
    }
}

void HelloTriangle::cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
