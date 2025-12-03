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
    // make sure our version checking function works, here's an example! It requires a minimum version of 0.0.0 and
    // will work for ALL versions less than 1.0.0!
    //
    // a program can be made to work with multiple major versions by combining a check for multiple versions and
    // running different implementations of user functions based on the version of the library being used!
    //
    // (this is equivalent to check_version(0), but the minor version/patch number, allowNewer flag are included for
    // the sake of clarity)
    bENGINE_ASSERT(bEngine::Utils::check_version(0, 0, 0, true), "Invalid bEngine version used!");

    // print out a message so we know we're actually using this method to create the (main) application:
    INFO_MSG("Initialization function for the 'Hello World' example!");

    // create a window for this example, when it is closed the application will terminate
    INFO_MSG("Creating a window for the example project.");
    const auto mainWindowHandle = app->add_window(bEngine::bEngineWindow::create_window(1280, 720));

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
    INFO_MSG(std::format("Update ({} ms)!", deltaTime * 1000.0));
}

/// @brief the tick function for the application which occurs as frequently as the inverse of the tick length
/// @param tickLength the amount of time (in seconds) corresponding to one tick
void tick(const double tickLength)
{
    INFO_MSG(std::format("Tick ({} ms)!", tickLength * 1000.0));
}

/// @brief frees the "user data" associated with the application
/// @param app a const pointer to the const application which is owned by the library; const because there should be
/// no need to actually impact the application at this point, just data which may have been created/allocated during
/// the run of the program due to user actions
void shutdown(const bEngine::bEngineApp *const app)
{
    // any data which would not be automatically freed or which must be freed in a specific order should be freed in
    // this function

    // print out a message so we know we're actually using this method to create the (main) application:
    INFO_MSG("Resource freeing function for the 'Hello World' example!");
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
    bEngineApp app{bEngineApp::create_app("Hello World", initialize, nullptr, 1.0 / 60.0, nullptr, shutdown)};

    /// @brief returns an instance of the application class so the library can access the user-defined/configured
    /// application
    /// @return a reference to a user defined application which may contain user-defined
    /// initialization/update/tick/shutdown functions
    bEngineApp &get_app()
    {
        return app;
    }
} // namespace bEngine