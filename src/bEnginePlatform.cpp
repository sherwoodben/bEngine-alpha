#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEnginePlatform.h"

/// @file bEnginePlatform.cpp
/// @brief implementations for the bEnginePlatform.h file

#include "bEngineUtilities.h"

// WINDOWS implementations
#ifdef WIN32

#    include <GLFW\glfw3.h>

const bool bEngine::Platform::initialize_platform_backends()
{
    const auto glfwResult = glfwInit();
    if (!glfwResult)
    {
        ERROR_MSG("Failed to initialize GLFW.");
        return false;
    }

    return true;
}

void bEngine::Platform::free_platform_backends()
{
    glfwTerminate();
}

void bEngine::Platform::poll_platform_events()
{
    glfwPollEvents();
}

const double bEngine::Platform::get_time()
{
    return glfwGetTime();
}

#endif // WIN32
