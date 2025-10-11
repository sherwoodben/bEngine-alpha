# GLFW (with Premake!)

The main GLFW repository and all its documentation can be found [here](https://github.com/glfw/glfw).

This fork provides a '/premake/' directory and a 'premake5.lua' script which can be included in other premake scripts to include glfw as a library in another project.

Any "extra" data/files associated with CMake or documentation have been removed; see the original glfw repository for documentation (and also for CMake). Some files associated with the original repository have also been removed (the "/.github/" directory, for example).

Examples and tests were also removed. Additionally, the "/deps/" directory was removed __which may cause issues targeting certain platforms__, specifically those using Wayland. To be completely honest, this is because I'm not sure how to handle these dependencies with a Premake approach. At this point, I'm happy to wait to deal with that issue until a need to target those platforms arises! I believe the other files (those unrelated to Wayland) in the "/deps/" directory were used for examples and tests, so those have been removed as well.

The (release, static) binary can be compiled in "stand-alone" mode _without_ being included in another project with the provided batch files.

When used as an "included" premake5.lua file (that is, glfw is a dependency to be linked/built by another Premake project) this premake5.lua file expects two configurations to be defined: "Debug" and "Release". These set the runtime as appropriate. Premake will automatically attempt to set the runtime for any other configuration it might encounter (as per the Premake documentation).

# PLATFORMS

At this point, only Windows platforms are supported.

It should not take too much work to support Unix/Linux platforms.

Platforms requiring Wayland are __NOT__ supported at this time and attempting to target these platforms will fail unless extra care is taken to ensure the dependencies are available and the system knows where to find them.