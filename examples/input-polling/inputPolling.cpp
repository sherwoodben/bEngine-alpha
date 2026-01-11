/// @file inputPolling.cpp
/// @brief demonstrates how to check for inputs, etc.
/// @note very basic for now and subject to change in the future!

#include <bEngineApp.h> // for access to the bEngineApp class and creation function
#include <bEngineInput.h> // for access to the bEngineInput struct (which is technically included in the bEngineWindow header)
#include <bEngineUtilities.h> // for printing information to the console to prove we're actually using the desired functions
#include <bEngineWindow.h> // for access to the bEngineWindow class and creation function

#include <format>
#include <vector>

/// @brief we'll use the bEngine namespace just so we don't need to prepend everything with bEngine::
/// @note this probably isn't the 'best' practice!
using namespace bEngine;

namespace
{
    /// @brief store the handle for the main window
    unsigned int g_mainWindowHandle{0};

    /// @brief prints the input state (but only the parts which are different from the last time it was called!)
    /// @param inputState the input state to print the associated state of
    void print_input_state(const bEngineInputState &inputState)
    {
        // keep a list of all of the names of the pressed keys/mouse buttons as well as the current mouse position
        std::vector<std::string>  pressedKeyNames{};
        std::vector<std::string>  pressedMouseButtonNames{};
        std::pair<double, double> mouseAxisValues{0.0, 0.0};

        // loop through all of the key codes bEngine recognizes and add the ones which are pressed to the list of
        // pressed key names
        for (bEngineKeyCode keyCode = bEngineKeyCode::first; keyCode != bEngineKeyCode::last; ++keyCode)
        {
            if (inputState.get_key_state(keyCode))
            {
                pressedKeyNames.push_back(Input::get_keycode_name(keyCode));
            }
        }

        // do the same for the mouse buttons:
        for (bEngineMouseButtonCode mouseButtonCode = bEngineMouseButtonCode::first;
             mouseButtonCode != bEngineMouseButtonCode::last;
             ++mouseButtonCode)
        {
            if (inputState.get_mouse_button_state(mouseButtonCode))
            {
                pressedMouseButtonNames.push_back(Input::get_mouse_button_code_name(mouseButtonCode));
            }
        }

        // store the mouse position...
        mouseAxisValues.first  = inputState.get_mouse_axis_state(bEngineMouseAxisCode::mouse_x);
        mouseAxisValues.second = inputState.get_mouse_axis_state(bEngineMouseAxisCode::mouse_y);

        // build strings which concatenate the pressed keys/mouse buttons into one string for convenience of printing to
        // the console... we also want to keep track of the previous values so we don't spam the same values to the
        // console when we're printing information!
        std::string pressedKeysString{""};
        std::string pressedMouseButtonsString{""};

        static std::string               lastPressedKeysString{""};
        static std::string               lastPressedMouseButtonsString{""};
        static std::pair<double, double> lastMouseAxisValues{0.0, 0.0};

        // build the pressed keys string
        for (const auto &name : pressedKeyNames)
        {
            pressedKeysString.append(name);
            pressedKeysString.append(1, ' ');
        }

        // build the pressed mouse buttons string
        for (const auto &name : pressedMouseButtonNames)
        {
            pressedMouseButtonsString.append(name);
            pressedMouseButtonsString.append(1, ' ');
        }

        // only update the last pressed keys string if the new value is different; likewise only print the new value if
        // the value is different!
        if (pressedKeysString != lastPressedKeysString)
        {
            INFO_MSG(std::format("[EXAMPLE] PRESSED KEYS: {}", pressedKeysString));
            lastPressedKeysString = pressedKeysString;
        }

        // do the same for the mouse buttons
        if (pressedMouseButtonsString != lastPressedMouseButtonsString)
        {
            INFO_MSG(std::format("[EXAMPLE] PRESSED MOUSE BUTTONS: {}", pressedMouseButtonsString));
            lastPressedMouseButtonsString = pressedMouseButtonsString;
        }

        // and the mouse position
        if (mouseAxisValues != lastMouseAxisValues)
        {
            INFO_MSG(std::format("[EXAMPLE] MOUSE POSITION: ({}, {})", mouseAxisValues.first, mouseAxisValues.second));
            lastMouseAxisValues = mouseAxisValues;
        }
    };
} // namespace

/// @brief initializes the main window and stores the (global) handle to the main window
///
/// in other words, this is a place to configure data/load resources you will use in the remaining user defined
/// functions!
/// @param app a reference to the application which is owned by the library; useful for setting up window(s), etc.
/// @return true if initalization/loading was successful and the program can continue, or false if the program
/// should close/crash/terminate
const bool initialize(bEngineApp *const app)
{
    // create a window for this example, when it is closed the application will terminate... but we can't rely on the
    // engine to do this automatically in this example!
    g_mainWindowHandle = app->add_window(bEngineWindow::create_window(1280, 720));

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
    const auto mainWindow = get_app().get_window(g_mainWindowHandle);
    if (!mainWindow)
    {
        INFO_MSG("[EXAMPLE] The main window has been closed. Quitting the application.");
        get_app().quit();
        return;
    }

    // now we want to get the input state associated with the main window:
    const auto &inputState = mainWindow->get_input_state();

    // here's how we check if a specific key is pressed; in this case 'escape' which will close the window (which will
    // quit the app).
    if (inputState.get_key_state(bEngineKeyCode::key_escape))
    {
        INFO_MSG("[EXAMPLE] Pressed 'escape'. Closing the window.");
        mainWindow->set_should_close(true);
        return;
    }

    // and now print the input state!
    print_input_state(inputState);
}

namespace bEngine
{
    /// @brief store an instance of the app statically-- here is where we "connect" the above functions into the
    /// application class!
    /// @note since we provide an update function, the app will not automatically quit when all windows are closed. That
    /// means we need to account for when the main window closes ourself in the update function! The same would be true
    /// in the tick method if that were to be implemented instead of the update method
    bEngineApp app{bEngineApp::create_app("Input Polling", initialize, update)};

    /// @brief returns an instance of the application class so the library can access the user-defined/configured
    /// application
    /// @return a reference to a user defined application which may contain user-defined
    /// initialization/update/tick/shutdown functions
    bEngineApp &get_app()
    {
        return app;
    }
} // namespace bEngine