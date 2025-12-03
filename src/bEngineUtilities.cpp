#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineUtilities.h"

/// @file bEngineUtilities.cpp
/// @brief implementations for the bEngineUtilities.h file

#include "autoversion.h" // for access to versioning macros

using namespace bEngine;

const bool Utils::check_version(
    const unsigned int major,
    const unsigned int minor,
    const unsigned int patch,
    const bool         allowNewer)
{
    // the major version must match exactly because a major version represents a breaking change
    if (get_major_version() != major)
        return false;

    // the minor version and patch numbers must match exactly _only if_ newer versions are not allowed
    if (!allowNewer)
    {
        if ((get_minor_version() == minor) && ((get_patch_number() == patch)))
            return true;
        else
            return false;
    }

    // if newer versions _are_ acceptable, there's an order to ensuring things work. for example, consider the following
    // values for version numbers:
    //
    //  - 2.0.16
    //  - 2.1.5
    //
    // clearly, no breaking changes have been introduced (the major versions are the same); the minor version is greater
    // _but the patch number is lower_. Still, this represents a "more updated" version of the library! We just need to
    // keep that in mind so we don't compare the patch number if a newer minor version is being used
    if (get_minor_version() >= minor || (get_minor_version() == minor && (get_patch_number() >= patch)))
        return true;
    else
        return false;
}

const char *const Utils::get_version_string()
{
    return BENGINE_ALPHA_VERSION_STRING;
}

const unsigned int Utils::get_major_version()
{
    return BENGINE_ALPHA_VERSION_MAJOR;
}

const unsigned int Utils::get_minor_version()
{
    return BENGINE_ALPHA_VERSION_MINOR;
}

const unsigned int Utils::get_patch_number()
{
    return BENGINE_ALPHA_VERSION_PATCH;
}

const char *const Utils::get_commit_hash()
{
    return BENGINE_ALPHA_COMMIT_HASH;
}