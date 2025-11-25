#pragma once

/// @file bEngineApp.h
/// @brief the interface for an app in the bEngine library

#include <bEngineWindow.h>

#include <memory>
#include <string>
#include <vector>

namespace bEngine
{
    class bEngineApp;
    typedef const bool (*app_init_fn)(bEngineApp *const app);
    typedef void (*app_shutdown_fn)(const bEngineApp *const app);

    typedef void (*app_update_fn)(const double deltaTime);
    typedef void (*app_tick_fn)(const double tickLength);

    class bEngineApp
    {
      private:
        static const std::string s_defaultAppName;

      public:
        static bEngineApp create_app(
            std::string   &&name       = std::string{s_defaultAppName},
            app_init_fn     initFn     = nullptr,
            app_update_fn   updateFn   = nullptr,
            double          tickLength = 1.0 / 60.0,
            app_tick_fn     tickFn     = nullptr,
            app_shutdown_fn shutdownFn = nullptr);

      private:
        const std::string                           m_name{s_defaultAppName};
        const app_init_fn                           m_initFn{nullptr};
        app_update_fn                               m_updateFn{nullptr};
        double                                      m_tickLength{1.0 / 60.0};
        app_tick_fn                                 m_tickFn{nullptr};
        const app_shutdown_fn                       m_shutdownFn{nullptr};
        bool                                        m_isRunning{true};
        std::vector<std::unique_ptr<bEngineWindow>> m_windows;

        struct AppToken
        {
        };

      public:
        bEngineApp()  = delete;
        ~bEngineApp() = default;
        bEngineApp(
            AppToken        token,
            std::string   &&name,
            app_init_fn     initFn,
            app_update_fn   updateFn,
            double          tickLength,
            app_tick_fn     tickFn,
            app_shutdown_fn shutdownFn);

      public:
        const unsigned int add_window(std::unique_ptr<bEngineWindow>&& newWindow);

        const bool initialize();

        void quit();

        void run();

        void set_tick_length(const double tickLength);

        void shutdown() const;
    };

    extern bEngineApp &get_app();
} // namespace bEngine