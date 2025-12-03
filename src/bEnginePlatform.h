#pragma once

/// @file bEnginePlatform.h
/// @brief the declarations for the platform specific functions which will need to be implemented on a per-platform
/// basis

namespace bEngine
{
    /// @brief platform specific functions/methods which will be implemented on a per-platform basis
    namespace Platform
    {
        /// @brief sets up the "context" for the application to run in
        /// @return true if all backends were initialized successfully, false if not (which _should_ lead to the program
        /// terminating)
        const bool initialize_platform_backends();

        /// @brief frees/"releases" the "context" the application runs in
        void free_platform_backends();

        /// @brief gets the program's current timer value
        /// @return the value of the program's timer (in seconds)
        const double get_time();

        /// @brief polls the platform for system/platform/window level events
        void poll_platform_events();
    } // namespace Platform
} // namespace bEngine