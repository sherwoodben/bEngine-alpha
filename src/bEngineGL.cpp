#include "bEnginePCH.h" // include first since we're utilizing the PCH

#include "bEngineGL.h"

/// @file bEngineGL.cpp
/// @brief implementations for the bEngineGL.h file

#include "bEngineUtilities.h" // for access to info messages, etc.

namespace
{
    const bool platform_load_gl_function_pointers(bEngine::bEngineGL &gl);
}

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
    isValid = isValid && AttachShader;
    isValid = isValid && BindBufferBase;
    isValid = isValid && BindFramebuffer;
    isValid = isValid && BindSampler;
    isValid = isValid && BindTextureUnit;
    isValid = isValid && BindVertexArray;
    isValid = isValid && BlendFunc;
    isValid = isValid && BlitNamedFramebuffer;
    isValid = isValid && CheckNamedFramebufferStatus;
    isValid = isValid && ClearNamedFramebufferfi;
    isValid = isValid && ClearNamedFramebufferfv;
    isValid = isValid && CompileShader;
    isValid = isValid && CreateBuffers;
    isValid = isValid && CreateFramebuffers;
    isValid = isValid && CreateProgram;
    isValid = isValid && CreateSamplers;
    isValid = isValid && CreateShader;
    isValid = isValid && CreateTextures;
    isValid = isValid && CreateVertexArrays;
    isValid = isValid && DeleteBuffers;
    isValid = isValid && DeleteFramebuffers;
    isValid = isValid && DeleteProgram;
    isValid = isValid && DeleteSamplers;
    isValid = isValid && DeleteShader;
    isValid = isValid && DeleteTextures;
    isValid = isValid && DeleteVertexArrays;
    isValid = isValid && DetachShader;
    isValid = isValid && Disable;
    isValid = isValid && DrawArrays;
    isValid = isValid && DrawArraysInstanced;
    isValid = isValid && Enable;
    isValid = isValid && GetProgramInfoLog;
    isValid = isValid && GetProgramiv;
    isValid = isValid && GetShaderInfoLog;
    isValid = isValid && GetShaderiv;
    isValid = isValid && GetTextureImage;
    isValid = isValid && LinkProgram;
    isValid = isValid && NamedBufferStorage;
    isValid = isValid && NamedBufferSubData;
    isValid = isValid && NamedFramebufferTexture;
    isValid = isValid && PixelStorei;
    isValid = isValid && ProgramUniform4fv;
    isValid = isValid && ProgramUniformMatrix4fv;
    isValid = isValid && SamplerParameterf;
    isValid = isValid && SamplerParameterfv;
    isValid = isValid && SamplerParameterIiv;
    isValid = isValid && SamplerParameterIuiv;
    isValid = isValid && SamplerParameteri;
    isValid = isValid && SamplerParameteriv;
    isValid = isValid && ShaderSource;
    isValid = isValid && TextureParameteri;
    isValid = isValid && TextureStorage2D;
    isValid = isValid && TextureSubImage2D;
    isValid = isValid && UseProgram;
    isValid = isValid && Viewport;

    return isValid;
}

const bool bEngine::load_gl_function_pointers(bEngineGL &gl)
{
    // reset the provided struct just in case it's been loaded into before:
    gl = {};

    // delegate to the platform-specific function pointer loading method; if unsuccessful return false
    const bool platformGLSuccess = platform_load_gl_function_pointers(gl);
    if (!platformGLSuccess)
    {
        return false;
    }

    // return the validity of the loaded gl "context" which is only true if all of the desired gl function pointers were
    // loaded
    return gl.is_valid();
}

#ifdef WIN32

#    include <glad\gl.h> // for GL function pointer loading

namespace
{
    const bool platform_load_gl_function_pointers(bEngine::bEngineGL &gl)
    {
        INFO_MSG("[PLATFORM] Loading GL function pointers with glad.");

        // the glad gl context to load all function pointers into, from which we'll cherry pick the ones we actually
        // want
        GladGLContext gladGL{};

        // load the glad gl function pointers
        const auto gladSuccess = gladLoaderLoadGLContext(&gladGL);

        // return false if there was an error loading the glad gl function pointers
        if (!gladSuccess)
        {
            return false;
        }

        // now we just copy the desired function pointer values into our GL struct!
        gl.AttachShader                = gladGL.AttachShader;
        gl.BindBufferBase              = gladGL.BindBufferBase;
        gl.BindFramebuffer             = gladGL.BindFramebuffer;
        gl.BindSampler                 = gladGL.BindSampler;
        gl.BindTextureUnit             = gladGL.BindTextureUnit;
        gl.BindVertexArray             = gladGL.BindVertexArray;
        gl.BlendFunc                   = gladGL.BlendFunc;
        gl.BlitNamedFramebuffer        = gladGL.BlitNamedFramebuffer;
        gl.CheckNamedFramebufferStatus = gladGL.CheckNamedFramebufferStatus;
        gl.ClearNamedFramebufferfi     = gladGL.ClearNamedFramebufferfi;
        gl.ClearNamedFramebufferfv     = gladGL.ClearNamedFramebufferfv;
        gl.CompileShader               = gladGL.CompileShader;
        gl.CreateBuffers               = gladGL.CreateBuffers;
        gl.CreateFramebuffers          = gladGL.CreateFramebuffers;
        gl.CreateProgram               = gladGL.CreateProgram;
        gl.CreateSamplers              = gladGL.CreateSamplers;
        gl.CreateShader                = gladGL.CreateShader;
        gl.CreateTextures              = gladGL.CreateTextures;
        gl.CreateVertexArrays          = gladGL.CreateVertexArrays;
        gl.DeleteBuffers               = gladGL.DeleteBuffers;
        gl.DeleteFramebuffers          = gladGL.DeleteFramebuffers;
        gl.DeleteProgram               = gladGL.DeleteProgram;
        gl.DeleteSamplers              = gladGL.DeleteSamplers;
        gl.DeleteShader                = gladGL.DeleteShader;
        gl.DeleteTextures              = gladGL.DeleteTextures;
        gl.DeleteVertexArrays          = gladGL.DeleteVertexArrays;
        gl.DetachShader                = gladGL.DetachShader;
        gl.Disable                     = gladGL.Disable;
        gl.DrawArrays                  = gladGL.DrawArrays;
        gl.DrawArraysInstanced         = gladGL.DrawArraysInstanced;
        gl.Enable                      = gladGL.Enable;
        gl.GetProgramInfoLog           = gladGL.GetProgramInfoLog;
        gl.GetProgramiv                = gladGL.GetProgramiv;
        gl.GetShaderInfoLog            = gladGL.GetShaderInfoLog;
        gl.GetShaderiv                 = gladGL.GetShaderiv;
        gl.GetTextureImage             = gladGL.GetTextureImage;
        gl.LinkProgram                 = gladGL.LinkProgram;
        gl.NamedBufferStorage          = gladGL.NamedBufferStorage;
        gl.NamedBufferSubData          = gladGL.NamedBufferSubData;
        gl.NamedFramebufferTexture     = gladGL.NamedFramebufferTexture;
        gl.PixelStorei                 = gladGL.PixelStorei;
        gl.ProgramUniform4fv           = gladGL.ProgramUniform4fv;
        gl.ProgramUniformMatrix4fv     = gladGL.ProgramUniformMatrix4fv;
        gl.SamplerParameterf           = gladGL.SamplerParameterf;
        gl.SamplerParameterfv          = gladGL.SamplerParameterfv;
        gl.SamplerParameterIiv         = gladGL.SamplerParameterIiv;
        gl.SamplerParameterIuiv        = gladGL.SamplerParameterIuiv;
        gl.SamplerParameteri           = gladGL.SamplerParameteri;
        gl.SamplerParameteriv          = gladGL.SamplerParameteriv;
        gl.ShaderSource                = gladGL.ShaderSource;
        gl.TextureParameteri           = gladGL.TextureParameteri;
        gl.TextureStorage2D            = gladGL.TextureStorage2D;
        gl.TextureSubImage2D           = gladGL.TextureSubImage2D;
        gl.UseProgram                  = gladGL.UseProgram;
        gl.Viewport                    = gladGL.Viewport;

        // unload the glad gl context (not strictly needed)
        gladLoaderUnloadGLContext(&gladGL);

        // the platform-loading portion went correctly, so return true! It is up to another method to determine if the
        // gl context which was passed to store the function pointers in is actually valid or not
        return true;
    };
} // namespace
#endif // WIN32