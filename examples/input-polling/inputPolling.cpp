/// @file inputPolling.cpp
/// @brief demonstrates how to check for inputs, etc.
/// @note very basic for now and subject to change in the future!

#include <bEngineApp.h> // for access to the bEngineApp class and creation function
#include <bEngineInput.h> // for access to the bEngineInput struct (which is technically included in the bEngineWindow header)
#include <bEngineUtilities.h> // for printing information to the console to prove we're actually using the desired functions
#include <bEngineWindow.h> // for access to the bEngineWindow class and creation function

#include <format>
#include <vector>

namespace
{
    /// @brief store the handle for the main window
    unsigned int mainWindowHandle{0};
} // namespace

/// @brief initializes the "user data" associated with the application
///
/// in other words, this is a place to configure data/load resources you will use in the remaining user defined
/// functions!
/// @param app a reference to the application which is owned by the library; useful for setting up window(s), etc.
/// @return true if initalization/loading was successful and the program can continue, or false if the program
/// should close/crash/terminate
const bool initialize(bEngine::bEngineApp *const app)
{
    // create a window for this example, when it is closed the application will terminate... but we can't rely on the
    // engine to do this automatically in this example!
    INFO_MSG("Creating a window for the example project.");
    mainWindowHandle = app->add_window(bEngine::bEngineWindow::create_window(1280, 720));

    // assume all other initialization went well; this is just the barebones example after all; return true so the
    // app continues to load/initialize
    //
    // returning false would result in the program crashing

    return true;
}

/// @brief the update function for the application which occurs as often as possible
/// @param deltaTime the amount of time (in seconds) since the last run of the update function
void update(const double deltaTime)
{
    // we have to be sure to quit the app if the window is closed...
    const auto mainWindow = bEngine::get_app().get_window(mainWindowHandle);
    if (!mainWindow)
    {
        INFO_MSG("The main window has been closed. Quitting the application.");
        bEngine::get_app().quit();
        return;
    }

    const auto inputState = mainWindow->get_input_state();

    std::vector<std::string>  pressedKeyNames;
    std::vector<std::string>  pressedMouseButtonNames;
    std::pair<double, double> mouseAxisValues;

    for (bEngine::bEngineKeyCode keyCode = bEngine::bEngineKeyCode::first; keyCode != bEngine::bEngineKeyCode::last;
         keyCode                         = ++keyCode)
    {
        if (inputState.get_key_state(keyCode))
        {
            pressedKeyNames.push_back(bEngine::get_keycode_name(keyCode));
        }
    }

    for (bEngine::bEngineMouseButtonCode mouseButtonCode = bEngine::bEngineMouseButtonCode::first;
         mouseButtonCode != bEngine::bEngineMouseButtonCode::last;
         mouseButtonCode = ++mouseButtonCode)
    {
        if (inputState.get_mouse_button_state(mouseButtonCode))
        {
            pressedMouseButtonNames.push_back(bEngine::get_mouse_button_code_name(mouseButtonCode));
        }
    }

    mouseAxisValues.first  = inputState.get_mouse_axis_state(bEngine::bEngineMouseAxisCode::mouse_x);
    mouseAxisValues.second = inputState.get_mouse_axis_state(bEngine::bEngineMouseAxisCode::mouse_y);

    static std::string               lastPressedKeysString{""};
    static std::string               lastPressedMouseButtonsString{""};
    static std::pair<double, double> lastMouseAxisValues;

    std::string pressedKeysString{""};
    std::string pressedMouseButtonsString{""};

    for (const auto &name : pressedKeyNames)
    {
        pressedKeysString.append(name);
        pressedKeysString.append(1, ' ');
    }

    for (const auto &name : pressedMouseButtonNames)
    {
        pressedMouseButtonsString.append(name);
        pressedMouseButtonsString.append(1, ' ');
    }

    if (pressedKeysString != lastPressedKeysString)
    {
        INFO_MSG(std::format("PRESSED KEYS: {}", pressedKeysString));
        lastPressedKeysString = pressedKeysString;
    }

    if (pressedMouseButtonsString != lastPressedMouseButtonsString)
    {
        INFO_MSG(std::format("PRESSED MOUSE BUTTONS: {}", pressedMouseButtonsString));
        lastPressedMouseButtonsString = pressedMouseButtonsString;
    }

    if (mouseAxisValues != lastMouseAxisValues)
    {
        INFO_MSG(std::format("MOUSE POSITION: ({}, {})", mouseAxisValues.first, mouseAxisValues.second));
        lastMouseAxisValues = mouseAxisValues;
    }
}

/// @brief the tick function for the application which occurs as frequently as the inverse of the tick length
/// @param tickLength the amount of time (in seconds) corresponding to one tick
void tick(const double tickLength)
{
    // do nothing in this example
}

/// @brief frees the "user data" associated with the application
/// @param app a const pointer to the const application which is owned by the library; const because there should be
/// no need to actually impact the application at this point, just data which may have been created/allocated during
/// the run of the program due to user actions
void shutdown(const bEngine::bEngineApp *const app)
{
    // do nothing in this example
}

namespace bEngine
{
    /// @brief store an instance of the app statically-- here is where we "connect" the above functions into the
    /// application class!
    /// @note since we provide an update function, the app will not automatically quit when all windows are closed. That
    /// means we need to account for when the main window closes ourself in the update function! The same would be true
    /// in the tick method if that were to be implemented instead of the update method
    bEngineApp app{bEngineApp::create_app("Input Polling", initialize, update, 1.0 / 60.0, nullptr, shutdown)};

    /// @brief returns an instance of the application class so the library can access the user-defined/configured
    /// application
    /// @return a reference to a user defined application which may contain user-defined
    /// initialization/update/tick/shutdown functions
    bEngineApp &get_app()
    {
        return app;
    }
} // namespace bEngine