#pragma once

/// @file bEngineWindow.h
/// @brief the interface for a window in the bEngine library

#include <memory>
#include <string>

namespace bEngine
{
    class bEngineWindow;

    typedef void (*window_render_fn)(const bEngineWindow *const window);

    class bEngineWindow
    {
      private:
        static const std::string s_defaultWindowName;

      public:
        static std::unique_ptr<bEngineWindow> create_window(
            const int        width,
            const int        height,
            std::string    &&title    = std::string{s_defaultWindowName},
            window_render_fn renderFn = nullptr);

      private:
        inline static unsigned int s_windowCounter{0};

      private:
        const unsigned int m_windowID{s_windowCounter++};
        int                m_size[2]{0, 0};
        std::string        m_title{""};
        window_render_fn   m_renderFn{nullptr};

        struct PlatformWindowImpl;
        std::unique_ptr<PlatformWindowImpl> m_impl{nullptr};

        struct WindowToken
        {
        };

      public:
        bEngineWindow() = delete;
        ~bEngineWindow();
        bEngineWindow(
            WindowToken      token,
            const int        width,
            const int        height,
            std::string    &&title,
            window_render_fn renderFn);

      public:
        const bool get_should_close() const;

        const unsigned int get_window_ID() const;

        void render() const;
    };

} // namespace bEngine