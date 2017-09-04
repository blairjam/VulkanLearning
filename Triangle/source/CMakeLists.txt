set (SOURCE_FILES 
    main.cpp 
    HelloTriangle.cpp)

# Create executable.
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# Include project headers.
#target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_FILE_DIR})
# Include GLFW headers for the compiler.
target_include_directories (${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIR})

# Link the Vulkan and GLFW libraries.
target_link_libraries (${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries (${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES})