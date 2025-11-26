#pragma once

/// @file bEngineWindow.h
/// @brief the interface for a window in the bEngine library

#include <memory> // for access to unique _ptr for the PIMPL idiom
#include <string> // for access to strings

namespace bEngine
{
    // fwd declaration for the bEngineWindow class which is used as an argument in the render function typedef
    class bEngineWindow;

    /// @brief the typedef associated with a window render function; returns (void) given a pointer to the (const)
    /// window to render to
    typedef void (*window_render_fn)(const bEngineWindow *const window);

    /// @brief the bEngineWindow interface for interacting with the window/storing window data
    class bEngineWindow
    {
        // private static data
      private:
        /// @brief the default window name/title
        inline static const std::string s_defaultWindowName{"bEngine-alpha Window"};

        /// @brief the counter used for assigning ID numbers to windows; only ever increments when a window is
        /// instantiated
        inline static unsigned int s_windowCounter{0};

        // public static methods
      public:
        /// @brief window creation "factory" function which is to be used by the user instead of the window's ctor
        /// @param width the desired width of the window
        /// @param height the desired height of the window
        /// @param title the desired title of the window, or the default window title if not provided
        /// @param renderFn the function pointer to the desired render function for the window, or nullptr if not
        /// provided
        /// @return a unique pointer to the new window which was created with the provided arguments
        static std::unique_ptr<bEngineWindow> create_window(
            const int        width,
            const int        height,
            std::string    &&title    = std::string{s_defaultWindowName},
            window_render_fn renderFn = nullptr);

        // private members/data
      private:
        /// @brief the (unique) ID associated with the window
        ///
        /// the ID is automatically assigned on window creation and will be unique from any other window's ID during the
        /// run of an application
        const unsigned int m_windowID{s_windowCounter++};

        /// @brief the size of the window, in pixels
        ///
        /// [0] - width
        /// [1] - height
        int m_size[2]{0, 0};

        /// @brief the title of the window
        std::string m_title{""};

        /// @brief the window's (user provided) render function
        window_render_fn m_renderFn{nullptr};

        /// @the platform-specific window implementation; defined in the bEngineWindow.cpp file and must be implemented
        /// per-platform
        struct PlatformWindowImpl;

        /// @brief store a unique pointer to the PlatformWindowImpl as per the PIMPL idiom
        std::unique_ptr<PlatformWindowImpl> m_impl{nullptr};

        /// @brief to ensure a bEngineWindow is only constructible via the static "factory" method _while also_
        /// utilizing unique_ptr, we use the "passkey/token" idiom
        ///
        /// since the WindowToken struct is private, only the bEngineWindow app can instantiate it. Since the
        /// bEngineWindow ctor is public, it is accessibly by std::make_unique... BUT because ONLY bEngineWindow
        /// instances can create a WindowToken, ONLY bEngineWindow instances can make use of std::make_unique AND the
        /// ctor, effectively restricting the creation of bEngineWindows to the static "factory" method.
        struct WindowToken
        {
        };

        // (public) ctors and dtor
      public:
        /// @brief deafult ctor is insufficient
        bEngineWindow() = delete;

        /// @brief dtor must be defined in the bEngineWindow.cpp file where the full definition of the
        /// PlatformWindowImpl struct is known
        ~bEngineWindow();

        /// @brief ctor which takes the arguments required to construct a window
        /// @param token a token which can only be instantiated by the bEngineWindow struct, to restrict creation of
        /// bEngineWindow instances to the static factory method
        /// @param width the desired width of the window
        /// @param height the desired height of the window
        /// @param title the desired title for the window
        /// @param renderFn the desired render function for the window
        bEngineWindow(
            WindowToken      token,
            const int        width,
            const int        height,
            std::string    &&title,
            window_render_fn renderFn);

        // public methods/functions so the window can actually be used by the application
      public:
        /// @brief checks to see if this window should close or not
        ///
        /// this will be dependent on the platform's window implementation
        /// @return true if this window should close, false if not
        const bool get_should_close() const;

        /// @brief gets the ID associated with this window
        /// @return the ID associated with this window
        const unsigned int get_window_ID() const;

        /// @brief wraps the window's user-provided render function
        ///
        /// As a rough idea of the implementation (though not necessarily 100% accurate):
        /// - clears the window
        /// - ensures the window is targeted for rendering
        /// - renders
        /// - presents the result to the window
        void render() const;
    };

} // namespace bEngine