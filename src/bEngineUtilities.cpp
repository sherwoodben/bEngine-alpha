#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineUtilities.h"

/// @file bEngineUtilities.cpp
/// @brief implementations for the bEngineUtilities.h file

#include "autoversion.h" // for access to versioning macros

using namespace bEngine;

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