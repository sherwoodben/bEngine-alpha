/// @file rendering.cpp
/// @brief presents some rendering examples

#include <bEngineApp.h>       // for access to the bEngineApp class and creation function
#include <bEngineUtilities.h> // for printing information to the console to prove we're actually using the desired functions
#include <bEngineWindow.h> // for access to the bEngineWindow class and creation function

#include <format>

namespace
{
    unsigned int g_mainWindowHandle{UINT_MAX};
}

// the initialization function just creates the main window and stores the handle in the global variable
const bool initialize(bEngine::bEngineApp *const app)
{
    g_mainWindowHandle = app->add_window(bEngine::bEngineWindow::create_window(1280, 720));

    // assume all other initialization went well; this is just the barebones example after all; return true so the
    // app continues to load/initialize
    //
    // returning false would result in the program crashing

    return true;
}

/// @brief the render function for the application which occurs as often as possible
///
/// this allows the user to actually issue a render command  only as often as desired (i.e. one can keep track of the
/// time in an accumulator and only issue an actual render command when the accumulator is greater than a certain
/// value)
/// @param deltaTime the amount of time (in seconds) since the last run of the render function
void render(const double deltaTime)
{
    // just clear the window-- that's all for now!
    const auto mainWindow = bEngine::get_app().get_window(g_mainWindowHandle);

    // clear with a "red" color
    mainWindow->clear(1.0f, 0.0f, 0.0f);

    // we also need to be sure to present the results of the rendering with the window...
    mainWindow->present();
}

namespace bEngine
{
    bEngineApp app{bEngineApp::create_app("Hello World", initialize, nullptr, render, nullptr)};

    bEngineApp &get_app()
    {
        return app;
    }
} // namespace bEngine