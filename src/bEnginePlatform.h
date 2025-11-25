#pragma once

/// @file bEnginePlatform.h
/// @brief the declarations for the platform specific functions which will need to be implemented on a per-platform
/// basis

namespace bEngine
{
    namespace Platform
    {
        const bool initialize_platform_backends();
        void       free_platform_backends();

        void poll_platform_events();

        const double get_time();
    } // namespace Platform
} // namespace bEngine