#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineApp.h"

/// @file bEngineApp.cpp
/// @brief implementations for the bEngineApp.h file

#include "bEngineInput.h"     // for access to the input polling/processing functions
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
    app_render_fn   renderFn,
    app_shutdown_fn shutdownFn)
    : m_name{name},
      m_initFn{initFn},
      m_updateFn{updateFn},
      m_renderFn{renderFn},
      m_shutdownFn{shutdownFn} { };

bEngine::bEngineApp bEngine::bEngineApp::create_app(
    std::string   &&name,
    app_init_fn     initFn,
    app_update_fn   updateFn,
    app_render_fn   renderFn,
    app_shutdown_fn shutdownFn)
{
    // we can simply call the ctor _inside_ this method since it's a static method of the bEngineApp and the ctor is
    // private; this enforces the use of this "factory" function
    return bEngine::bEngineApp{std::move(name), initFn, updateFn, renderFn, shutdownFn};
}

void bEngine::bEngineApp::shutdown() const
{
    INFO_MSG("[APPLICATION] Running shutdown function.");

    // we only want to attempt to call the user-provided function if it actually exists!
    if (m_shutdownFn)
        m_shutdownFn(this);
}

const unsigned int bEngine::bEngineApp::add_window(std::unique_ptr<bEngineWindow> &&newWindow)
{
    // move the new window into the vector if windows
    m_windows.emplace_back(std::move(newWindow));

    // since we know the window is at the back of the vector, return the ID of the window at the back of the vector
    // (i.e. the ID of the new window!)
    return m_windows.back()->get_window_ID();
}

void bEngine::bEngineApp::close_window(const unsigned int windowID)
{
    // will be nullptr if the provided windowID is not actually the ID of a window
    bEngineWindow *window{get_window(windowID)};

    // only close the window if we actually found a window
    if (window)
    {
        window->set_should_close(true);
    }
}

bEngine::bEngineWindow *const bEngine::bEngineApp::get_window(const unsigned int windowID)
{
    bEngineWindow *window{nullptr};

    // loop through all of the windows in the vector of windows; if the ID of the window matches the desired ID, set the
    // pointer we'll return to that window
    for (const auto &w : m_windows)
    {
        if (w->get_window_ID() == windowID)
        {
            window = w.get();
            break;
        }
    }

    // return the window pointer, which is nullptr if the provided windowID is not actually the ID of a window
    return window;
}

const bool bEngine::bEngineApp::initialize()
{
    INFO_MSG("[APPLICATION] Running initialization function.");

    // we only want to attempt to call the user-provided function if it actually exists!
    if (m_initFn)
        return m_initFn(this);

    // TO-DO: general application initialization stuff, if needed!

    // return true to indicate everything initialized correctly
    return true;
}

void bEngine::bEngineApp::quit()
{
    INFO_MSG("[APPLICATION] Quitting.");

    m_isRunning = false;
}

void bEngine::bEngineApp::run()
{
    INFO_MSG("[APPLICATION] Running main loop.");

    // declare some timing variables
    double lastTime{bEngine::Platform::get_time()};
    double tickAccumulator{0.0};

    // the loop continues while the app is still running...
    while (m_isRunning)
    {
        // if the update function is nullptr AND and there are no windows the app doesn't actually do anything... in
        // that case just quit (by setting the "isRunning" flag to false and trying to do another loop!
        if (!m_updateFn && m_windows.empty())
        {
            INFO_MSG("[APPLICATION] The application has no windows and no update function. It will now quit.");
            quit();
            continue;
        }

        // first, poll the system for events
        bEngine::Platform::poll_platform_events();

        // then update the timing variables and calculate the time since the last check:
        double currentTime{bEngine::Platform::get_time()};
        double deltaTime{currentTime - lastTime};

        // then, update each window, passing the amount of time to use to update values (i.e. deltaTime!)
        //
        // this also updates the input state for each window
        for (auto &window : m_windows)
        {
            window->update(deltaTime);
        }

        tickAccumulator += deltaTime;

        // we update as frequently as possible, passing the deltaTime to the user defined update function
        if (m_updateFn)
            m_updateFn(deltaTime);

        // do the same with the render function
        if (m_renderFn)
            m_renderFn(deltaTime);

        // now we'll check for windows which should close; if they shouldn't close we'll move them into a new vector
        // then replace the old vector with the new vector, which will call the destructor for the windows in the old
        // "moved into" vector
        std::vector<std::unique_ptr<bEngine::bEngineWindow>> openWindows;
        for (auto &window : m_windows)
        {
            if (window && !window->get_should_close())
            {
                openWindows.emplace_back(std::move(window));
            }
        }
        m_windows = std::move(openWindows);

        // set the last time to the current time so calculations will be accurate next time through the loop!
        lastTime = currentTime;
    }
}