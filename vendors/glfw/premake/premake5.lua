-- glfw premake script v1.1
-- Benjamin Sherwood, 2025

-- assume that if we're calling this premake file we are NOT building glfw "individually"
-- that is, it is instead being built as a dependency for another project. At this point,
-- we will _always and only_ build as a static library

-- in this case, we _could_ create a special workspace for "vendor" libraries, OR we could
-- just stick this project in the GLOBAL workspace. That's the option we'll go with, making
-- use of the special '*' workspace name. THIS WILL NOT WORK if there is not actually a
-- workspace that has been defined! In other words, be sure to INCLUDE this premake file in
-- the "parent" premake file!

-- we also provide an option to make a "stand-alone" version which _will_ provide a workspace
newoption
{
    trigger = "stand-alone",
    description = "generates a workspace for the library, enabling it to be built individually"
}

if  _OPTIONS["stand-alone"] then
    workspace "glfw"
        platforms { "Windows" }
        configurations { "Release" }
end

project "glfw"
    location "%{wks.location}/../build/"
    kind "StaticLib"
    language "C"
    architecture "x64"

    targetdir "%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    objdir "%{prj.location}/obj/%{cfg.platform}/%{cfg.buildcfg}"
    debugdir "%{prj.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"

    staticruntime "on"

    filter "configurations:Debug"
        runtime "Debug"
    filter "configurations:Release"
        runtime "Release"
    filter {}

    defines { "_CRT_SECURE_NO_WARNINGS" }

    includedirs { "../include/" }

    -- to be quite frank; I'm not entirely sure how I came up with this list of
    -- "platform agnostic" files... but it seems to be correct!
    files
    {
        "../src/glfw_config.h",
        "../src/context.c",
        "../src/init.c",
        "../src/input.c",
        "../src/monitor.c",
        "../src/vulkan.c",
        "../src/window.c",
        "../src/platform.c",
        "../src/null_init.c",
        "../src/null_monitor.c",
        "../src/null_window.c",
        "../src/null_joystick.c",
    }

    -- now we need to handle platform-specific files...
    -- these filters will be updated as more platforms are added!

    filter "platforms:Windows"
        defines { "_GLFW_WIN32" }

        -- we can use wildcard matching to get all the win32 specific files...
        -- similar to the note above, I'm not 100% sure how the windows specific files
        -- were determined... or if they're all necessary!
        --
        -- I only make use of OpenGL (for now) so the other files might not be needed,
        -- but for the sake of completeness this works!
        files
        {
            "../src/win32*.c",
            "../src/wgl_context.c",
            "../src/egl_context.c",
            "../src/osmesa_context.c"
        }

    filter{}