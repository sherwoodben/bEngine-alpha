--[[
    Populates various files in the project directory based on the git tag information if available

    this module provided a means to populate an "autoversion.h" file as well as a Doxyfile for documentation

    If no git tag information is available, default values which may not represent the true version of the project are used
--]]

local function get_git_tag()
    -- attempt to get the git tag for the folder
    local gitTag, errorCode = os.outputof("git describe --long --dirty --tags")

    -- if the tag was NOT found, give a warning
    if (errorCode ~= 0) then
        print("Warning: `git describe --long --dirty --tags` failed with error code", errorCode, gitTag)
    end

    return gitTag, errorCode
end

local function populate_autoversion(prjName, gitTag, errorCode)
    -- read the contents of the autoversion.h input file
    local autoversionContent = io.readfile("../tools/autoversion.h.in")

    -- if the tag was found, populate the input files with the data in the tag
    if (errorCode == 0) then
        print("Git tag: ", gitTag)
        parts = string.explode(gitTag, "-", true)
        local dirtyTag = ""
        if (tonumber(parts[2]) > 0) then
            dirtyTag = "+"
        end
        -- replace the placeholders in the autoversion file with the correct data...
        autoversionContent = autoversionContent:gsub("@VERSION_STRING@", parts[1] .. dirtyTag)
        versionNums = string.explode(parts[1], ".", true)
        autoversionContent = autoversionContent:gsub("@VERSION_MAJOR@", tostring(versionNums[1]))
        autoversionContent = autoversionContent:gsub("@VERSION_MINOR@", tostring(versionNums[2]))
        autoversionContent = autoversionContent:gsub("@VERSION_PATCH@", tostring(versionNums[3]))
        autoversionContent = autoversionContent:gsub("@COMMIT_HASH@", parts[3])
    -- if the tag was not found, populate the input files with default values
    else
        print("Populating files with default values which may not reflect the true version number.")
        autoversionContent = autoversionContent:gsub("@VERSION_STRING@", "0.0.0")
        autoversionContent = autoversionContent:gsub("@VERSION_MAJOR@", "0")
        autoversionContent = autoversionContent:gsub("@VERSION_MINOR@", "0")
        autoversionContent = autoversionContent:gsub("@VERSION_PATCH@", "0")
        autoversionContent = autoversionContent:gsub("@COMMIT_HASH@", "")
    end

    -- be sure to update the project name so the macros actually make sense!
    -- (replace any spaces or dashes with underscores)
    autoversionContent = autoversionContent:gsub("@PROJECT_NAME@", prjName:gsub("[ -]", "_"):upper())

    -- write the autoversion.h file to the ../src/ directory
    local f, err = os.writefile_ifnotequal(autoversionContent, path.join("../src/", "autoversion.h"))
    if (f) then
        print("Generated autoversion.h...")
    else
        print("Could not create autoversion.h! ", err)
    end
end

local function populate_doxyfile(prjName, gitTag, errorCode)
        -- read the contents of the autoversion.h input file
    local doxygenContent = io.readfile("../tools/Doxyfile.in")

    -- if the tag was found, populate the input files with the data in the tag
    if (errorCode == 0) then
        parts = string.explode(gitTag, "-", true)
        doxygenContent = doxygenContent:gsub("@VERSION_STRING@", parts[1])
    -- if the tag was not found, populate the input files with default values
    else
        print("Populating files with default values which may not reflect the true version number.")
        doxygenContent = doxygenContent:gsub("@VERSION_STRING@", "")
    end

    -- be sure to update the project name so the macros actually make sense!
    -- (replace any spaces or dashes with underscores)
    doxygenContent = doxygenContent:gsub("@PROJECT_NAME@", prjName:gsub("[ -]", "_"):upper())
    
    -- write the autoversion.h file to the ../src/ directory
    local f, err = os.writefile_ifnotequal(doxygenContent, path.join("../tools/", "Doxyfile"))
    if (f) then
        print("Generated Doxygen file...")
    else
        print("Could not create Doxygen file! ", err)
    end
end

local autopopulate = {} -- create a table to represent the module

function autopopulate.populate_files(prjName)
    local gitTag, errorCode = get_git_tag()
    populate_autoversion(prjName, gitTag, errorCode)
    populate_doxyfile(prjName, gitTag, errorCode)
end





return autopopulate