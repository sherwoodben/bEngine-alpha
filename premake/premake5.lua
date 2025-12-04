--[[
########################################################################################################################
    bEngine-alpha premake script v1.0
    Benjamin Sherwood, 2025
########################################################################################################################
    this script replaces the "Ultimate" C++ premake build script which was used before this point

    while that script "works" in simple cases, I found a whole bunch of small errors that compounded to make
    things hard to manage. I might refactor the ultimate build script in the future, but for now we can hard
    code the bEngine-alpha premake script!

    that being said, some of the functions which were developed for the previous script are still helpful, so they have
    been split into separate files for convenience/organization.
--]]

-- build the project name from the current working directory (actually the parent of
-- the current working directory because we're in the /premake/ subdirectory)
local PROJECT_NAME = string.gsub(os.getcwd(), ".*/([^/]+)/[^/]+/?$", "%1")

-- each dependency which is to be built in the solution/linked to the bEngine framework library
-- MUST be included here
--
-- it is expected these dependencies correspond to a directory in the /vendors/ directory of the same name which
-- also contains a /premake/ subdirectory for more granular control of how each dependency is built
--
-- only dependencies which are shared across ALL platforms should be put in the initial declaration; a filter
-- is provided for each platform to add specific dependencies when building the solution on a per-platform basis
local dependenciesToBuild = {}

-- the autopopulator module helps populate various files with information taken from the current git tag
local filePopulator = require("../tools/autopopulator")

--[[
    makes the workspace/solution and all of the projects which are included in the
    workspace/solution
--]]
local function build_workspace_and_projects()
    -- first, set up the workspace
    printf("Configuring workspace.")

    -- Generate a workspace with the desired name (i.e. append " Suite" to the project name)
    workspace(PROJECT_NAME .. " Suite")
    -- Set the start project to the main project
    startproject(PROJECT_NAME)
    -- Set the available configurations
    configurations{"Debug", "Release",}
    -- Set the available platforms
    platforms{"Windows",}
    -- Debug preprocessor definitions
    filter "configurations:Debug*"
        defines{"DEBUG",}
    -- Release preprocessor definitions
    filter "configurations:Release*"
        defines{"RELEASE",}
    filter{}
    -- Build with symbols
    symbols "On"

    -- as previously mentioned, each platform will now add the required per-platform dependencies
    filter "platforms:Windows"
        table.insert(dependenciesToBuild, "glfw")
        table.insert(dependenciesToBuild, "miniaudio")
    filter{}
    
    -- next, make any other projects (i.e. dependencies) we build
    printf("Configuring dependencies.")
    group "Dependencies"
        for idx, val in ipairs(dependenciesToBuild) do
            printf("Including additional premake script: %s", val)
            include("../vendors/" .. val .. "/premake")
        end
    
    -- then generate the main project
    group ""
    printf("Configuring the main project.")
    project(PROJECT_NAME)
        -- Set the project location to the /build/ directory
        location "%{wks.location}/../build/"
        -- Set the output/obj/debug directories based on their platform and build config
        targetdir "%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
        objdir "%{prj.location}/obj/%{cfg.platform}/%{cfg.buildcfg}"
        debugdir "%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
        -- The language is C++
        language "C++"
        -- 64 bit architecture
        architecture "x64"
        -- Default to C++20
        cppdialect "C++20"
        -- staticruntime/runtime configurations
        staticruntime "on"
        filter "configurations:Debug*"
            runtime "Debug"
        filter "configurations:Release*"
            runtime "Release"
        filter {}
        -- for now, we ONLY build as a static library
        kind "StaticLib"

        -- since we're building a library, we would typically want to define bNO_ENTRY_POINT... that being said,
        -- the library actually does expect to contain an entry point because the user will instead supply functions
        -- to be used in a predefined order, so we actually end up undefining this in the main.cpp file. To save a
        -- step, we just won't define bNO_ENTRY_POINT here!

        -- call the module responsible for populating the various input files with the correct project information
        filePopulator.populate_files(PROJECT_NAME)

        -- we need to be sure to include all of the vendor include directories AS WELL as the public include directory
        -- for the library
        includedirs
        {
            "../include/",
            "../vendors/*/include/"
        }

        -- now we need to be sure to flag the appropriate files for building...
        files
        {
            "../include/*.*",
            "../src/*.*"
        }

        -- lastly, we need to link the various libraries we're building
        for idx, val in ipairs(dependenciesToBuild) do
            links(val)
        end

    -- Lastly, make the examples
    group "Examples"
        include("../examples/premake/")
end

--[[
    an actual implementation of the "clean" action

    triggered by "clean", it removes the entire '/build/' directory and any file generated by premake

    Note: this does NOT remove the populated autoversion/doxygen files
--]]
newaction {
  trigger = "clean",
  description = "removes the '/build/' directory and any other file generated by premake (besides 'config.json')",
  execute = function() -- short enough to just define here!
    printf("\nRemoving the '/build/' directory and all its contents.")
    os.rmdir("../build/")
    printf("Removing (generated) content from the '/premake/' directory.")
    os.rmdir(".vs")
    os.remove("*.sln")
    printf("\nDone.\n")
  end,
}

--[[
    Of course, this should only run on a "build" action. Calls the build_workspace_and_projects() function
    to build the workspace/solution and all other projects! 
--]]
if (_ACTION ~= nil) then -- got some weird errors when running "help" without this...
  if (_ACTION == "codelite" or string.find(_ACTION, "gmake") or
    string.find(_ACTION, "vs20") or _ACTION == "xcode4") then
    build_workspace_and_projects()
  end
end