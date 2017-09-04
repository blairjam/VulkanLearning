# Min version 3.7, because we utilized FindVulkan.
cmake_minimum_required (VERSION 3.7)

set (PROJECT_NAME "Triangle")

project (${PROJECT_NAME})

# Set the output directories for the types of builds.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Set the Vulkan SDK location.
set (ENV{VULKAN_SDK} "/home/conner/Code/Libraries/VulkanSDK/1.0.57.0/x86_64")
# Set the pkg-config executable location.
set (ENV{PKG_CONFIG} "/usr/bin/pkg-config")

set (HEADER_FILE_DIR "${CMAKE_BINARY_DIR}/headers")
set (SOURCE_FILE_DIR "${CMAKE_BINARY_DIR}/source")

# Extra compiler and linker flags.
set (COMPILE_FLAGS "-I${HEADER_FILE_DIR}")
set (LINK_FLAGS "")

# Set C++14 standard.
set (CMAKE_CXX_STANDARD 14)

# Find pkg-config.
find_package (PkgConfig REQUIRED)

# Use pkg-config to assess GLFW options.
pkg_check_modules (GLFW REQUIRED glfw3)

# Append extra compiler and linker flags.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

# Find the Vulkan SDK.
find_package (Vulkan REQUIRED)

add_subdirectory (${SOURCE_FILE_DIR})
