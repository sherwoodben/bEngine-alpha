> [!Warning]
> This README is based on that of an old/private attempt at an engine/framework. The attempt was actually going quite well, then I got busy and needed a JSON library and it fell to the wayside a bit. This new project (bEngine-alpha) is a resurrection of that project, using the better practices I know now. That being said, the README may not be 100% accurate to the current state of the project. By version 1.0.0, this README will be completely up to date!
>
> However, this also means the public API is subject to change at any point. After the release of 1.0.0 a stable API will be maintained but until that point almost anything can change at any time! Documentation will be kept as up to date as possible, though it may not be 100% accurate during initial development phases.

# bEngine-alpha Overview

bEngine-alpha (henceforth bEngine) is a framework[^1] for creating games/applications for multiple target platforms using (and possibly abstracting) OpenGL. bEngine is designed to be fairly simple/low level, mostly providing:

- an application interface for interacting with the system/windows/platform
- (planned) classes for wrapping GL objects for easier use and to manage their lifetime on the GPU; this may also lead to abstracting away all need for the end user to actually call GL functions
- an entry point for an application, so the user only needs to supply a handful of function definitions which will be used by the application in a pre-defined sequence

[^1]: Is it a framework? A library? Who knows! Hopefully it's useful, though! As such, bEngine may be referred to as a framework or a library throughout the documentation, depending on the context or vibes.

> [!Note]
> At this point, the only platform that is actually implemented is Windows. That being said, the Windows platform utilizes glad/glfw, so extending to Linux/Unix-like systems shouldn't be terribly difficult-- I just don't have the means to test these configurations right now! Still, the framework is (hopefully) being developed in such a way that supporting other platforms is "just" a matter of replacing some platform specific implementations!

# Installation

To install bEngine, simply clone the directory to your desired location:

	git clone https://github.com/sherwoodben/bEngine-alpha

This will install the latest stable version of bEngine. A specific version of bEngine can be installed via the use of tags:

	git clone --branch <version> https://github.com/sherwoodben/bEngine-alpha [--depth 1]

where `<version>` is the tag corresponding to the desired version number which follows the MAJOR.MINOR.PATCH format.

> [!Tip]
> `--depth 1` is optional, but will install bEngine with a "snapshot" of the history at the version number rather than including the entire history. This is useful if you're developing an application which utilizes bEngine and not bEngine itself!

# Building

> [!Note]
> At this point, bEngine has only been developed/tested on Windows using Visual Studio 2022. The provided batch files assume the user will _also_ be building on the Windows platform in Visual Studio 2022 (or Visual Studios Insiders 2026). If this is not the case, the provided batch file should be edited to reflect the selected toolchain (if still on the Windows platform). If not on the Windows platform, you'll need to follow the [steps for generating files for the selected toolchain on your selected platform](https://premake.github.io/docs/Using-Premake). The Visual Studios Insiders 2026 batch files are untested, as I prefer Visual Studio 2022 at this time.

bEngine is configured to use premake to generate a Visual Studio (2022/2026) solution which contains as projects:

- The bEngine framework library itself
- Dependencies/vendor libraries
	- GLFW (on Windows platforms)
	- ~~Dear ImGui~~ (Not currently implemented)
- Example applications which consume/utilize bEngine

The user must provide a copy of the premake5 executable in the `/premake/` directory. Batch files has been provided in the `/premake/` directory which have the following effects when run[^2], assuming the executable is also in the directory (or available on the system path):

1. Several files are generated with the correct version information, pulled from the git tag (i.e. the version tag).
2. A Visual Studio (2022/2026) solution is generated containing projects for the bEngine library as well as several other libraries that must be built.

Open the generated solution, select a target configuration and platform, then build the entire solution. All resulting binaries including libraries and example executables are then found in `/build/bin/<platform>/<configuration>/`.

___If___ a third party library is required that is not to be built during this project's build step, explicit details/documentation will be provided as to _what_ is needed and _where_ it must be located.

[^2]: Don't just take my word for it and run random batch files! Go ahead and take a look to make sure everything looks good.

# Usage

This section will be detailed as the contents of the repository mature.

For now, documentation in the form of doxygen comments have been provided for all bEngine header files. If doxygen[^3] is installed on your system, the provided batch files in the `/tools/` directory can be used to documentation (html format) for a detailed overview of the library.

[^3]: Additionally, the default generated Doxyfile is configured to expect the "dot" tool from graphviz be available on the system. If the dot tool is not available on the system, the values in the `/tools/Doxyfile.in` file can be adjusted to reflect the absence of dot. When the batch file to generate the solution file is run, the Doxyfile will be created/updated to reflect the changes to `/tools/Doxyfile.in`.
