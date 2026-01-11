#pragma once

/// @file bEngineApp.h
/// @brief the interface for an app in the bEngine library

#include <memory> // for access to unique_ptr which is used to store the bEngineWindows associated with the application
#include <string> // for strings
#include <vector> // for storing a collection of bEngineWindows which are managed by the application

/// @brief the bEngine namespace is used to organize the classes/structs/types/functions associated with the bEngine
/// library
namespace bEngine
{

    // fwd declaration for the bEngineApp type which is used as an argument in the (user provided) applicatio
    // initialization/shutdown functions
    class bEngineApp;

    /// @brief application initialization function signature typedef; returns a const bool indicating initialization
    /// success given a pointer to the application to be initialized
    typedef const bool (*app_init_fn)(bEngineApp *const app);

    /// @brief application update function signature typedef; returns (void) given the amount of time since the last
    /// update
    typedef void (*app_update_fn)(const double deltaTime);

    /// @brief application render function signature typedef; returns (void) given the amount of time since the last
    /// call to this method-- allows the user to keep track of frame rates, multiple windows, etc.
    typedef void (*app_render_fn)(const double tickLength);

    /// @brief application shutdown function signature typedef; returns (void) given a pointer to the application to be
    /// initialized
    typedef void (*app_shutdown_fn)(const bEngineApp *const app);

    // fwd declaration for the bEngineWindow class which the application stores a vector of unique_ptrs of
    class bEngineWindow;

    /// @brief the bEngineApp class provides an interface for the library to run the application as well as a static
    /// method which is to be used to create an application by providing various function pointers which will be used by
    /// the framework
    class bEngineApp
    {
        // private static data
      private:
        /// @brief the default application name
        ///
        /// constructed from the version string/commit hash associated with the compiled version of bEngine
        static const std::string s_defaultAppName;

        // public static method(s)
      public:
        /// @brief static "factory" function to create an application, ensures the application ctor cannot be called by
        /// the user directly
        /// @param name the desired name for the application, or the default application name if not provided
        /// @param initFn the initialization function to be used by the application, or nullptr if not provided
        /// @param updateFn the update function to be used by the application, or nullptr if not provided
        /// @param renderFn the render function for the application, or nullptr if not provided
        /// @param shutdownFn the shutdown function to be used by the application, or nullptr if not provided
        /// @return a bEngineApp which operates with the provided functions as the initialization, update, render, and
        /// shutdown functions
        static bEngineApp create_app(
            std::string   &&name       = std::string{s_defaultAppName},
            app_init_fn     initFn     = nullptr,
            app_update_fn   updateFn   = nullptr,
            app_render_fn   renderFn   = nullptr,
            app_shutdown_fn shutdownFn = nullptr);

        // private data
      private:
        /// @brief the name associated with the application
        const std::string m_name{s_defaultAppName};

        /// @brief the function pointer to the (user provided) initialization function
        const app_init_fn m_initFn{nullptr};

        /// @brief the function pointer to the (user provided) update function
        const app_update_fn m_updateFn{nullptr};

        /// @brief the render function for the application; can render to multiple windows at various frame rates if
        /// managed correctly
        const app_render_fn m_renderFn{nullptr};

        /// @brief the function pointer to the (user provided) shutdown function
        const app_shutdown_fn m_shutdownFn{nullptr};

        /// @brief a flag which dictates whether the application is running (true) or if it should close (false)
        bool m_isRunning{true};

        /// @brief the windows owned/managed by the application
        std::vector<std::unique_ptr<bEngineWindow>> m_windows;

        // private ctor
      private:
        /// @brief ctor which takes all of the arguments required to construct an application
        /// @param name the desired name of the application
        /// @param initFn the desired (user-provided) initialization function of the application
        /// @param updateFn the desired (user-provided) update function of the application
        /// @param renderFn the desired (user-provided) render function for the application
        /// @param shutdownFn the desired (user-provided) shutdown function of the application
        bEngineApp(
            std::string   &&name,
            app_init_fn     initFn,
            app_update_fn   updateFn,
            app_render_fn   renderFn,
            app_shutdown_fn shutdownFn);

        // public ctor/dtor
      public:
        /// @brief default ctor is insufficient
        bEngineApp() = delete;

        /// @brief default dtor is acceptable
        ~bEngineApp() = default;

        // public functions/methods
      public:
        /// @brief adds a window to the application and returns the ID associated with the new window
        /// @param newWindow the new window to be added to the application
        /// @return the ID associated with the new window
        const unsigned int add_window(std::unique_ptr<bEngineWindow> &&newWindow);

        /// @brief sets the "should close" flag of the window (identified by the windowID) to "true"
        /// @param windowID the handle of the window to close
        ///
        /// if an invalid windowID is provided, nothing happens!
        ///
        /// @note there may or may not be an actual "flag" which is stored in the window struct _OR_ it might be managed
        /// behind the scenes by the platform's window management backend
        void close_window(const unsigned int windowID);

        /// @brief gets the window associated with the windowID such that the window can be resized, the input state of
        /// the window can be checked, etc.
        /// @param windowID the ID of the window to retrieve
        /// @return a pointer to the window identified by the provided ID, or nullptr if no such window exists
        bEngineWindow *const get_window(const unsigned int windowID);

        /// @brief runs the (user-provided) initialization function and general application setup
        /// @return true if the user provided a initialization function and it succeeds OR if the user did NOT provide
        /// an initialization function and general initialization succeeds; returns false if the user-provided
        /// initialization function fails or general initialization fails
        const bool initialize();

        /// @brief quits the application (i.e. sets the application's "running" flag to false)
        void quit();

        /// @brief runs the application's main loop
        ///
        /// involves polling input (per-window), calling into the user-provided update/render functions, etc.
        void run();

        /// @brief runs the application's (user-provided) shutdown function
        void shutdown() const;
    };

    /// @brief returns a reference to the (main) bEngineApp used by the program
    ///
    /// this function _MUST_ be implemented by the user; it _MAY_ "store" a static instance of the application and
    /// return that, or it might return a reference to a global application, etc.
    /// @return a reference to the (main) bEngineApp used by the program
    extern bEngineApp &get_app();
} // namespace bEngine