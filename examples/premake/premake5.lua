-- Add PROJECTS to this file as needed!

-- Or, if it makes more sense to store examples in subdirectories, maybe add
-- a premake5.lua file to the subdirectory and include it here!

-- ALL of the examples will have the same basic location/includes, etc; so we'll make
-- a function to do that as many times as we need:
function set_example_project_defaults()
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

    -- get all of the library include directories (in addition to the bEngine library!)
    local allLibIncludeDirs = cv.libraryIncludeDirs
    table.insert(allLibIncludeDirs, "../include/")
    for idx, val in ipairs(cv.libraryIncludeDirs) do
        if val ~= "" then
            includedirs("../" .. val)
        end
    end

    -- link all of the libraries (in addition to the bEngine library!)
    links {
        "bEngine-alpha",
    }

    -- link platform-specific libraries
    filter "platforms:Windows"
        -- I'm not entirely sure this is needed at the application level, but we'll include it anyway.
        -- included in the Windows platform filter because this is the only place glfw is linked for now.
        defines { "_CRT_SECURE_NO_WARNINGS" }
        links
        {
            "glfw"
        }
    filter {}
end

project "hello-world"
    set_example_project_defaults()
    files { "../hello-world/**.*", }
    
