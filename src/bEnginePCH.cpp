#ifdef _WIN32
#    define GLAD_GL_IMPLEMENTATION ///< since glad was generated as a single-file header, we need a place for the actual
                                   ///< implementation to live; define the macro here as per the glad documentation
#endif
#include "bEnginePCH.h"

/// @file bEnginePCH.cpp
/// @brief ensures the precompiled header is actually compiled, and allows a location to delcare implementation macros
/// for header-only libraries