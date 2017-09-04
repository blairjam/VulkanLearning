#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>

#include "HelloTriangle.hpp"

int main()
{
    HelloTriangle tri;

    try
    {
        tri.run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
