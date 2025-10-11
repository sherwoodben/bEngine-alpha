// include the autoversion header here just to ensure it's included in the build. Can also add version
// requirements/assertions here if needed!
#include "autoversion.h"

// if the "build tests" flag was set to true during configuration, the tests exectuble is actually built by compiling
// this	file with the bUnitTests header included in this file...
#ifdef bBUILD_TESTS
#    define bTEST_IMPLEMENTATION ///< as per the bUnitTests documentations
#    include "bUnitTests.h"      ///< "header only" unit testing framework. Implementation "lives" in this file
#endif

// this just creates a macro 'bENTRY_POINT' to reflect the current configuration/platform's entry point
#if defined RELEASE && defined _WIN32
#    include <Windows.h>
#    define bENTRY_POINT() WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
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

// #undef bNO_ENTRY_POINT

// if we're building tests, the "bUnitTests.h" header already has a main function to use as the (test) application's
// entry point so we don't need to include another entry point. This even overrides the value set above!
//
// the 'bBUILD_TESTS' value is a unit testing application preprocessor definition, which should be defined by the
// testing application/through use of the configuration script-- if it's not defined then tests are not built!
#if (not defined bBUILD_TESTS && not defined bNO_ENTRY_POINT)

int bENTRY_POINT() { };

#endif // !bBUILD_TESTS && !bNO_ENTRY_POINT