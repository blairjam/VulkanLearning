#include <stdexcept>
#include <iostream>
#include <vector>
#include <list>
#include <string>

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

    // Tell GLFW not to create an OpenGL context.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Disable window resizing.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

    /*GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* primaryVidMode = glfwGetVideoMode(primaryMonitor);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, primaryMonitor, nullptr);
    //glfwSetWindowPos(window, (primaryVidMode->width - WINDOW_WIDTH) / 2, (primaryVidMode->height - WINDOW_HEIGHT) / 2);*/
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

    // Check GLFW extension information, and get the requirements for this system.
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
    // Get required GLFW extensions.
    *glfwExtensions = glfwGetRequiredInstanceExtensions(glfwExtensionCount);

    // Add the names of the extensions to a list. We will check that these extensions are supported later, and remove them if
    // they are available.
    std::list<std::string> requiredExtensions;
    for (auto i = 0; i < *glfwExtensionCount; i++)
    {
        requiredExtensions.push_back(*(*glfwExtensions + i));
    }

    uint32_t availableExtensionCount = 0;

    // Check number of available extensions.
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
    // Create vector to hold available extension data.
    std::vector<VkExtensionProperties> availableExtensions(availableExtensionCount);
    // Populate vector with available extension data.
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, availableExtensions.data());

    // Print out the list of available extensions.
    std::cout << "Available Extensions:" << std::endl;
    for (const auto& extension : availableExtensions)
    {
        bool req = false;

        // Check to see if the current extension is required.
        for (std::list<std::string>::iterator it = requiredExtensions.begin(); it != requiredExtensions.end(); it++)
        {
            // If the extension matches a required extension, mark the req flag as true, and remove the extension from the
            // required list.
            if (extension.extensionName == *it)
            {
                requiredExtensions.erase(it);
                req = true;
                break;
            }
        }

        std::cout << "\t" << extension.extensionName << (req ? " (Required)" : "") << std::endl;
    }

    // Print out any remaining extensions that aren't in the list of available ones.
    if (!requiredExtensions.empty())
    {
        std::cout << "These extensions are required but not available:" << std::endl;
        for (const auto& reqExt : requiredExtensions)
        {
            std::cout << "\t" << reqExt << std::endl;
        }
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
