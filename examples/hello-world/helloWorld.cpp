/// @file helloWorld.cpp
/// @brief represents the not-quite minimum (but EXTREMELY limited) features required to actually compile an
/// application!

#include <bEngineApp.h>       // for access to the bEngineApp class and creation function
#include <bEngineUtilities.h> // for printing information to the console to prove we're actually using the desired functions
#include <bEngineWindow.h> // for access to the bEngineWindow class and creation function

#include <format>

/// @brief initializes the "user data" associated with the application
///
/// in other words, this is a place to configure data/load resources you will use in the remaining user defined
/// functions!
/// @param app a reference to the application which is owned by the library; useful for setting up window(s), etc.
/// @return true if initalization/loading was successful and the program can continue, or false if the program
/// should close/crash/terminate
const bool initialize(bEngine::bEngineApp *const app)
{
    // print out a message so we know we're actually using this method to create the (main) application:
    INFO_MSG("[EXAMPLE] Initialization function for the 'Hello World' example!");

    // create a window for this example, when it is closed the application will terminate
    INFO_MSG("[EXAMPLE] Creating a window for the example project.");
    app->add_window(bEngine::bEngineWindow::create_window(1280, 720));

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
}

/// @brief the render function for the application which occurs as often as possible
///
/// this allows the user to actually issue a render command  only as often as desired (i.e. one can keep track of the
/// time in an accumulator and only issue an actual render command when the accumulator is greater than a certain
/// value)
/// @param deltaTime the amount of time (in seconds) since the last run of the render function
void render(const double deltaTime)
{
}

/// @brief frees the "user data" associated with the application
/// @param app a const pointer to the const application which is owned by the library; const because there should be
/// no need to actually impact the application at this point, just data which may have been created/allocated during
/// the run of the program due to user actions
void shutdown(const bEngine::bEngineApp *const app)
{
}

namespace bEngine
{
    /// @brief store an instance of the app statically-- here is where we "connect" the above functions into the
    /// application class!
    /// @note for now, the update/tick functions are not actually "connected" -- this is fine because the initialization
    /// function creates a window! Once that window is closed, the application will terminate. This can actually be used
    /// to create a "monolithic update/render" function which is passed to the window creation function! That would
    /// effectively tie updating and rendering together (which to be fair is the same as how the engine currently works
    /// but as threading is introduced this will change) which might be useful for creating an emulator, or a non-real
    /// time program, etc.
    bEngineApp app{bEngineApp::create_app(
        "Hello World",
        initialize,
        nullptr /* or 'update' */,
        nullptr /* or 'render' */,
        nullptr /* or 'shutdown' */)};

    /// @brief returns an instance of the application class so the library can access the user-defined/configured
    /// application
    /// @return a reference to a user defined application which may contain user-defined
    /// initialization/update/tick/shutdown functions
    bEngineApp &get_app()
    {
        return app;
    }
} // namespace bEngine