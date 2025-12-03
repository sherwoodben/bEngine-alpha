#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineApp.h"

/// @file bEngineApp.cpp
/// @brief implementations for the bEngineApp.h file

#include "bEnginePlatform.h"  // for access to platform-specific functions/methods
#include "bEngineUtilities.h" // for access to versioning functions and info/warning/error macros
#include "bEngineWindow.h"    // for access to the bEngineWindow class definition

#include <format> // for formatting the default app name

const std::string bEngine::bEngineApp::s_defaultAppName{std::format(
    "bEngine-alpha v{} ({}) Application",
    bEngine::Utils::get_version_string(),
    bEngine::Utils::get_commit_hash())};

bEngine::bEngineApp::bEngineApp(
    std::string   &&name,
    app_init_fn     initFn,
    app_update_fn   updateFn,
    double          tickLength,
    app_tick_fn     tickFn,
    app_shutdown_fn shutdownFn)
    : m_name{name},
      m_initFn{initFn},
      m_updateFn{updateFn},
      m_tickLength{tickLength},
      m_tickFn{tickFn},
      m_shutdownFn{shutdownFn} { };

bEngine::bEngineApp bEngine::bEngineApp::create_app(
    std::string   &&name,
    app_init_fn     initFn,
    app_update_fn   updateFn,
    double          tickLength,
    app_tick_fn     tickFn,
    app_shutdown_fn shutdownFn)
{
    return bEngine::bEngineApp{std::move(name), initFn, updateFn, tickLength, tickFn, shutdownFn};
}

void bEngine::bEngineApp::shutdown() const
{
    // we only want to attempt to call the user-provided function if it actually exists!
    if (m_shutdownFn)
        m_shutdownFn(this);
}

const unsigned int bEngine::bEngineApp::add_window(std::unique_ptr<bEngineWindow> &&newWindow)
{
    m_windows.emplace_back(std::move(newWindow));
    return m_windows.back()->get_window_ID();
}

const bool bEngine::bEngineApp::initialize()
{
    // we only want to attempt to call the user-provided function if it actually exists!
    if (m_initFn)
        return m_initFn(this);

    // now we do general application initialization stuff (if needed) and return true so long as everything goes well

    return true;
}

void bEngine::bEngineApp::quit()
{
    INFO_MSG("Quitting...");
    m_isRunning = false;
}

void bEngine::bEngineApp::run()
{
    // declare some timing variables
    double lastTime{bEngine::Platform::get_time()};
    double tickAccumulator{0.0};

    // the loop continues while the app is still running...
    while (m_isRunning)
    {
        // if the update function AND the tick function are nullptr, (and there are no windows) the app doesn't actually
        // do anything... in that case just quit (by setting the "isRunning" flag to false and trying to do another
        // loop!
        if (!m_updateFn && !m_tickFn && m_windows.empty())
        {
            WARNING_MSG("The application has no windows, update function, or tick function. It will now quit.");
            quit();
            continue;
        }

        // first, poll the system for events
        bEngine::Platform::poll_platform_events();

        // then update the timing variables and calculate the time since the last check:
        double currentTime{bEngine::Platform::get_time()};
        double deltaTime{currentTime - lastTime};
        lastTime = currentTime;

        tickAccumulator += deltaTime;

        // we update as frequently as possible, passing the deltaTime to the user defined update function
        if (m_updateFn)
            m_updateFn(deltaTime);

        // we tick as frequently as the tick rate (inverse of tick length) and we do multiple ticks if we somehow
        // lag/time-out
        while (m_tickFn && tickAccumulator >= m_tickLength)
        {
            m_tickFn(m_tickLength);
            tickAccumulator -= m_tickLength;
        }

        // now we'll check for windows which should close; if they should close we'll simply call the .reset() method
        // and if they shouldn't we'll move them into a new vector then replace the old vector with the new vector and
        std::vector<std::unique_ptr<bEngine::bEngineWindow>> openWindows;
        for (auto &window : m_windows)
        {
            if (window && window->get_should_close())
            {
                window.reset();
            }
            else if (window)
            {
                openWindows.emplace_back(std::move(window));
            }
        }
        m_windows = std::move(openWindows);

        // since we know all of the windows left in the vector are valid, we can just issue render commands to all of
        // them without worrying about nullptrs!
        for (auto &window : m_windows)
        {
            window->render();
        }
    }
}

void bEngine::bEngineApp::set_tick_length(const double tickLength)
{
    m_tickLength = tickLength;
}