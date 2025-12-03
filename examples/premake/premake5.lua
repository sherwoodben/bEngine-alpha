-- Add PROJECTS to this file as needed!

-- Or, if it makes more sense to store examples in subdirectories, maybe add
-- a premake5.lua file to the subdirectory and include it here!

-- ALL of the examples will have the same basic location/includes, etc; so we'll make
-- a function to do that as many times as we need:
local function set_example_project_defaults()
    location "%{wks.location}/../build/"
    filter "configurations:Debug"
        kind "ConsoleApp"
    filter "configurations:Release"
        kind "WindowedApp"
    filter{}

    -- Set the output/obj/debug directories
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

    -- include the bEngine public headers (we don't care about the implementation when we're building an app!)
    includedirs {
        "../../include/"
    }

    -- link to bEngine
    links {
        "bEngine-alpha",
    }
end

project "hello-world"
    set_example_project_defaults()
    files { "../hello-world/**.*", }
    
