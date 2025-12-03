#include "bEnginePCH.h" // include first since we're utilizing the PCH

// if the "build tests" flag was set to true during configuration, the tests exectuble is actually built by compiling
// this	file with the bUnitTests header included in this file...
#ifdef bBUILD_TESTS
#    define bTEST_IMPLEMENTATION // as per the bUnitTests documentations
#    include "bUnitTests.h"      // "header only" unit testing framework. Implementation "lives" in this file
#endif

// this just creates a macro 'bENTRY_POINT' to reflect the current configuration/platform's entry point
#if defined RELEASE && defined _WIN32
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif // !WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#    undef WIN32_LEAN_AND_MEAN
#    define bENTRY_POINT()                                                                                             \
        WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
#endif
#ifndef bENTRY_POINT
#    define bENTRY_POINT() main()
#endif

// IMPORTANT NOTE:
//
// If we are building an application (console or window), this serves as the (default) entry point to our program.
//
// Typically, libraries _do not_ have main functions, but in some cases they might! By default, libraries _will not_
// implement this main function. However, this behavior can be changed by editing this (default) file, or more
// specifically by uncommenting the following line:

#undef bNO_ENTRY_POINT

// if we're building tests, the "bUnitTests.h" header already has a main function to use as the (test) application's
// entry point so we don't need to include another entry point. This even overrides the value set above!
//
// the 'bBUILD_TESTS' value is a unit testing application preprocessor definition, which should be defined by the
// testing application/through use of the configuration script-- if it's not defined then tests are not built!
#if (not defined bBUILD_TESTS && not defined bNO_ENTRY_POINT)

// since this is the entry point when we're _NOT_ running tests and this section is only compiled in that case, we can
// put includes for some library files at this point:

#    include "bEngineApp.h"       // for access to the bEngineApp class so we can actually run the application
#    include "bEnginePlatform.h"  // for access to platform backend setup/shutdown functions
#    include "bEngineUtilities.h" // for printing information/error messages (in debug mode)

#    include <format> // for formatting info/error messages

/// @brief the actual entry point of an application which utilizes this framework
///
/// the internals of this function should basically be self-documenting, especially with the info/warning messages
/// @return 0 on success
int bENTRY_POINT()
{
    INFO_MSG(std::format(
        "Running bEngine-alpha v{} ({})",
        bEngine::Utils::get_version_string(),
        bEngine::Utils::get_commit_hash()));

    INFO_MSG("Preparing platform specific backends...");
    if (!bEngine::Platform::initialize_platform_backends())
    {
        ERROR_MSG("Platform initialization failed. Exiting with return code -1.");
        return -1;
    }

    INFO_MSG("Running the application initialization function...");
    auto &app = bEngine::get_app();
    if (!app.initialize())
    {
        ERROR_MSG("Application initialization failed. Exiting with return code -1.");
        return -1;
    }

    INFO_MSG("Running the application loop...");
    app.run();

    INFO_MSG("Running user data free function...");
    app.shutdown();

    INFO_MSG("Freeing platform specific backends...");
    bEngine::Platform::free_platform_backends();

    return 0;
};

#endif // !bBUILD_TESTS && !bNO_ENTRY_POINT
