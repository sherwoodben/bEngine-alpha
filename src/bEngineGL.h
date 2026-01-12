#pragma once

/// @file bEngineGL.h
/// @brief OpenGL related structs and function pointer loading method

namespace bEngine
{
    /// @brief a struct which contains function pointers for all of the OpenGL functions a bEngineApp uses
    struct bEngineGL
    {
        // to=do: add the GL function pointers bEngine utilizes!

        /// @brief checks whether this bEngineGL struct has all of the function pointers loaded
        /// @return true only if all of the function pointers are non nullptr, false otherwise (i.e. function pointers
        /// failed to load)
        const bool is_valid() const;
    };

    /// @brief loads the desired GL function pointers into the provided bEngineGL struct
    /// @param gl the bEngineGL struct which is to house the loaded function pointers
    /// @return true only if all function pointers were loaded successfully (i.e. the bEngineGL struct is "valid")
    const bool load_gl_function_pointers(bEngineGL &gl);
} // namespace bEngine