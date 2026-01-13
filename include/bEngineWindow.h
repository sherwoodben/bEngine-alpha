#pragma once

/// @file bEngineWindow.h
/// @brief the interface for a window in the bEngine library

#include <bEngineInput.h> // for access to the input state struct/functions

#include <memory> // for access to unique _ptr for the PIMPL idiom
#include <string> // for access to strings

namespace bEngine
{
    // fwd declaration for the bEngineWindow class which is used as an argument in the render function typedef
    class bEngineWindow;

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
        /// @return a unique pointer to the new window which was created with the provided arguments
        static std::unique_ptr<bEngineWindow> create_window(
            const int     width,
            const int     height,
            std::string &&title = std::string{s_defaultWindowName});

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

        /// @the platform-specific window implementation; defined in the bEngineWindow.cpp file and must be implemented
        /// per-platform
        ///
        /// each platform's PIMPL will also manage a GL context such that window drawing/rendering commands can use the
        /// correct function pointers; no need to actually expose the GL context struct however!
        struct PlatformWindowImpl;

        /// @brief store a unique pointer to the PlatformWindowImpl as per the PIMPL idiom
        std::unique_ptr<PlatformWindowImpl> m_impl{nullptr};

        /// @brief the input state associated with the window (i.e. which keys are down, where the mouse is, etc.)
        bEngineInputState m_inputState;

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
        bEngineWindow(WindowToken token, const int width, const int height, std::string &&title);

        // public methods/functions so the window can actually be used by the application
      public:
        /// @brief uses the desired color to clear the window
        /// @param r the red component to use for the color to clear the window with, defaults to 0.0
        /// @param r the green component to use for the color to clear the window with, defaults to 0.0
        /// @param r the blue component to use for the color to clear the window with, defaults to 0.0
        /// @param r the alpha component to use for the color to clear the window with, defaults to 1.0
        void clear(const float r = 0.0f, const float g = 0.0f, const float b = 0.0f, const float a = 1.0f) const;

        /// @brief gets the input state associated with the window
        /// @return the input state associated with the window (as a const reference)
        const bEngineInputState &get_input_state() const;

        /// @brief checks to see if this window should close or not
        ///
        /// this will be dependent on the platform's window implementation
        /// @return true if this window should close, false if not
        const bool get_should_close() const;

        /// @brief gets the ID associated with this window
        /// @return the ID associated with this window
        const unsigned int get_window_ID() const;

        /// @brief presents the results of the render commands which were issued to this window since the last time the
        /// present method was called (i.e. swaps the buffers)
        void present() const;

        /// @brief sets the window's 'should close' state
        /// @param shouldClose true means the window should close, false means it should not close
        void set_should_close(const bool shouldClose) const;

        /// @brief updates the window's input state, render accumulator, etc.
        /// @param deltaTime the amount of time to use to update values with (in seconds)
        void update(const double deltaTime);
    };

} // namespace bEngine