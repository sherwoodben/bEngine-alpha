#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEnginePlatform.h"

/// @file bEnginePlatform.cpp
/// @brief implementations for the bEnginePlatform.h file

#include "bEngineUtilities.h" // for access to error/info message macros

// WINDOWS implementations
#ifdef WIN32

#    include <GLFW\glfw3.h> // platform/window management is provided by GLFW
#    include <miniaudio.h>  // audio playback managed by miniaudio

namespace
{
    ma_engine audioEngine;
}

const bool bEngine::Platform::initialize_platform_backends()
{
    // attempt to load glfw
    const auto glfwResult = glfwInit();
    if (glfwResult)
    {
        INFO_MSG("Initialized glfw.");
    }
    else
    {
        ERROR_MSG("Failed to initialize GLFW.");
        return false;
    }

    // attempt to load miniaudio
    const auto miniaudioResult = (ma_engine_init(nullptr, &audioEngine) == MA_SUCCESS);
    if (miniaudioResult)
    {
        INFO_MSG("Initialized miniaudio.");
    }
    else
    {
        ERROR_MSG("Failed to initialize miniaudio.");
        return false;
    }

    return true;
}

void bEngine::Platform::free_platform_backends()
{
    INFO_MSG("Terminating glfw.");
    glfwTerminate();

    // NOTE: I've experienced strange bugs in other projects when closing the program which seemed to be caused by
    // miniaudio... see discussion here: https://github.com/glfw/glfw/issues/2709#issuecomment-2795110156
    //
    // The fix?
    //
    // Terminate the audio engine _after_ calling glfwTerminate
    INFO_MSG("Terminating miniaudio.");
    ma_engine_uninit(&audioEngine);
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
