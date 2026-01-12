#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineGL.h"

/// @file bEngineGL.cpp
/// @brief implementations for the bEngineGL.h file

const bool bEngine::bEngineGL::is_valid() const
{
    // assume the struct/context is valid to start:
    bool isValid{true};

    // remove the comments from the following line (and put the correct function pointer in the parentheses) to actually
    // check the validity of the context
    //
    // this follows short circuit logic, so if isValid is ever false it will return false eventually
    //
    // the function pointer is only non nullptr if the function pointer has been loaded correctly; checking all of the
    // function pointers allows us to ensure all function pointers have been loaded

    // isValid = isValid && (/*function pointer goes here*/);

    return isValid;
}

const bool bEngine::load_gl_function_pointers(bEngineGL &gl)
{
    // reset the provided struct just in case it's been loaded into before:
    gl = {};

    // to-do: implement gl function loading!

    // return the validity of the loaded gl "context"
    return gl.is_valid();
}
