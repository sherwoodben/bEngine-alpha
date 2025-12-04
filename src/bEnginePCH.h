#pragma once

/// @file bEnginePCH.h
/// @brief the pre-compiled header for the bEngine library

// (general) third-party includes
#include <glm\glm.hpp>          // for access to vec2, etc.
#include <glm\gtc\type_ptr.hpp> // so we can access vecs as float*, etc.

// general includes
#include <format>      // for formatting info/warning/general messages
#include <iostream>    // for access to the console for printing
#include <memory>      // for unique pointer to store windows, events, etc.
#include <queue>       // for storing events (which are unique pointers to the event interface)
#include <string>      // for access to strings
#include <type_traits> // for metaprogramming to ensure we only emit types which are actually events!
#include <vector>      // for the list of windows the application is managing

// now we move into the "platform-specific" includes, which will only be included for the indicated platforms!

// Windows:
// clang-format off
// (these must be in a specific order!)
#ifdef _WIN32
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif
#    include <Windows.h>    // for Windows entry point (WinMain)
#    include <glad\gl.h>    // for OpenGL functions, etc.
#    include <GLFW\glfw3.h> // for window management, input, etc.
#    include <miniaudio.h> // for audio playback
#    undef WIN32_LEAN_AND_MEAN
#endif
// clang-format on