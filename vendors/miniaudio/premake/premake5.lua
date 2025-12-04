-- miniaudio premake script v1.0
-- Benjamin Sherwood, 2025

-- assume that if we're calling this premake file we are NOT building miniaudio "individually"
-- that is, it is instead being built as a dependency for another project. At this point,
-- we will _always and only_ build as a static library

-- in this case, we _could_ create a special workspace for "vendor" libraries, OR we could
-- just stick this project in the GLOBAL workspace. That's the option we'll go with, making
-- use of the special '*' workspace name. THIS WILL NOT WORK if there is not actually a
-- workspace that has been defined! In other words, be sure to INCLUDE this premake file in
-- the "parent" premake file!
project "miniaudio"
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

    includedirs { "../include/" }

    files
    {
        "../src/miniaudio.c"
    }