# Min version 3.7, because we utilized FindVulkan.
cmake_minimum_required (VERSION 3.7)

set (PROJECT_NAME "VulkanTest")

project (${PROJECT_NAME})

# Set the output directories for the types of builds.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the Vulkan SDK location.
set (ENV{VULKAN_SDK} "/home/conner/Code/Libraries/VulkanSDK/1.0.57.0/x86_64")
# Set the pkg-config executable location.
set (ENV{PKG_CONFIG} "/usr/bin/pkg-config")

# Extra compiler and linker flags.
set (COMPILE_FLAGS "")
set (LINK_FLAGS "")

# Set C++14 standard.
set (CMAKE_CXX_STANDARD 14)

# Set source file locations.
set (SOURCE_FILES main.cpp)

# Find pkg-config.
find_package (PkgConfig REQUIRED)

# Use pkg-config to assess GLFW options.
pkg_check_modules (GLFW REQUIRED glfw3)

# Append extra compiler and linker flags.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

# Find the Vulkan SDK.
find_package (Vulkan REQUIRED)

# Create executable.
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# Include GLFW headers for the compiler.
target_include_directories (VulkanTest PUBLIC ${GLFW_INCLUDE_DIR})

# Link the Vulkan and GLFW libraries.
target_link_libraries (${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries (${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES})
