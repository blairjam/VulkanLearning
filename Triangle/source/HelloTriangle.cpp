#include <stdexcept>
#include <iostream>
#include <vector>

#include "HelloTriangle.hpp"

HelloTriangle::HelloTriangle()
{
}

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
    createInstance();
}

void HelloTriangle::createInstance()
{
    // Create a VkApplicationInfo struct to give to the VkInstaceCreateInfo struct.
    // This holds information about our application.
    VkApplicationInfo appInfo  = {};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = WINDOW_TITLE;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "No Engine.";
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    uint32_t glfwExtensionCount;
    const char** glfwExtensions;

    checkExtensions(&glfwExtensionCount, &glfwExtensions);

    // Create a VkInstaceCreateInfo struct to pass to the vkCreateInstance function.
    // This lets the Vulkan API know which extensions we want to use.
    VkInstanceCreateInfo createInfo    = {};
    createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo        = &appInfo;
    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount       = 0;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create a Vulkan instance.");
    }
}

void HelloTriangle::checkExtensions(uint32_t* glfwExtensionCount, const char*** glfwExtensions)
{
    uint32_t availableExtensionCount = 0;

    // Check number of available extensions.
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
    // Create vector to hold available extension data.
    std::vector<VkExtensionProperties> availableExtensions(availableExtensionCount);
    // Populate vector with available extension data.
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, availableExtensions.data());

    std::cout << "Available Extensions:" << std::endl;
    for (const auto& extension : availableExtensions)
    {
        std::cout << "\t" << extension.extensionName << std::endl;
    }

    // Get required GLFW extensions.
    *glfwExtensions = glfwGetRequiredInstanceExtensions(glfwExtensionCount);

    std::cout << "Required Extensions:" << std::endl;
    for (auto i = 0; i < *glfwExtensionCount; i++)
    {
        std::cout << "\t" << *(*glfwExtensions + i) << std::endl;
    }
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
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}
