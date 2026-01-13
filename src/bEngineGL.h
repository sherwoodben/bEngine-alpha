#pragma once

/// @file bEngineGL.h
/// @brief OpenGL related structs and function pointer loading method

namespace bEngine
{
    /// @brief a struct which contains function pointers for all of the OpenGL functions a bEngineApp uses
    struct bEngineGL
    {
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml];
        void (*AttachShader)(unsigned int program, unsigned int shader){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBufferBase.xhtml];
        void (*BindBufferBase)(unsigned int target, unsigned int index, unsigned int buffer){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindFramebuffer.xhtml];
        void (*BindFramebuffer)(unsigned int target, unsigned int framebuffer){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindSampler.xhtml];
        void (*BindSampler)(unsigned int unit, unsigned int sampler){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindTextureUnit.xhtml];
        void (*BindTextureUnit)(unsigned int unit, unsigned int texture){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml];
        void (*BindVertexArray)(unsigned int array){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml];
        void (*BlendFunc)(unsigned int sfactor, unsigned int dfactor){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBlitFramebuffer.xhtml];
        void (*BlitNamedFramebuffer)(
            unsigned int readFramebuffer,
            unsigned int drawFramebuffer,
            int          srcX0,
            int          srcY0,
            int          srcX1,
            int          srcY1,
            int          dstX0,
            int          dstY0,
            int          dstX1,
            int          dstY1,
            unsigned int mask,
            unsigned int filter){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCheckFramebufferStatus.xhtml];
        unsigned int (*CheckNamedFramebufferStatus)(unsigned int framebuffer, unsigned int target){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearBuffer.xhtml];
        void (*ClearNamedFramebufferfi)(
            unsigned int framebuffer,
            unsigned int buffer,
            int          drawbuffer,
            float        depth,
            int          stencil){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearBuffer.xhtml];
        void (*ClearNamedFramebufferfv)(
            unsigned int framebuffer,
            unsigned int buffer,
            int          drawbuffer,
            const float *value){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml];
        void (*CompileShader)(unsigned int shader){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateBuffers.xhtml];
        void (*CreateBuffers)(int n, unsigned int *buffers){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateFramebuffers.xhtml];
        void (*CreateFramebuffers)(int n, unsigned int *framebuffers){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml];
        unsigned int (*CreateProgram)(){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateSamplers.xhtml];
        void (*CreateSamplers)(int n, unsigned int *samplers){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml];
        unsigned int (*CreateShader)(unsigned int shaderType){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateTextures.xhtml];
        void (*CreateTextures)(unsigned int target, int n, unsigned int *textures){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateVertexArrays.xhtml];
        void (*CreateVertexArrays)(int n, unsigned int *arrays){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml];
        void (*DeleteBuffers)(int count, const unsigned int *framebuffers){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteFramebuffers.xhtml];
        void (*DeleteFramebuffers)(int count, const unsigned int *framebuffers){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml];
        void (*DeleteProgram)(unsigned int program){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteSamplers.xhtml];
        void (*DeleteSamplers)(int count, const unsigned int *samplers){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml];
        void (*DeleteShader)(unsigned int shader){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteTextures.xhtml];
        void (*DeleteTextures)(int count, const unsigned int *textures){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml];
        void (*DeleteVertexArrays)(int count, const unsigned int *arrays){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml];
        void (*DetachShader)(unsigned int program, unsigned int shader){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml];
        void (*Disable)(unsigned int cap){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml];
        void (*DrawArrays)(unsigned int mode, int first, int count){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArraysInstanced.xhtml];
        void (*DrawArraysInstanced)(unsigned int mode, int first, int count, int instanceCount){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml];
        void (*Enable)(unsigned int cap){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml];
        void (*GetProgramInfoLog)(unsigned int program, int maxLength, int *length, char *infoLog){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgram.xhtml];
        void (*GetProgramiv)(unsigned int program, unsigned int pname, int *params){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml];
        void (*GetShaderInfoLog)(unsigned int shader, int maxLength, int *length, char *infoLog){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShader.xhtml];
        void (*GetShaderiv)(unsigned int shader, unsigned int pname, int *params){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetTexImage.xhtml];
        void (*GetTextureImage)(
            unsigned int texture,
            int          level,
            unsigned int format,
            unsigned int type,
            int          bufSize,
            void        *pixels){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml];
        void (*LinkProgram)(unsigned int program){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferStorage.xhtml];
        void (*NamedBufferStorage)(unsigned int buffer, signed long long size, const void *data, unsigned int flags){
            nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferSubData.xhtml];
        void (
            *NamedBufferSubData)(unsigned int buffer, signed long long offset, signed long long size, const void *data){
            nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glFramebufferTexture.xhtml];
        void (*NamedFramebufferTexture)(
            unsigned int framebuffer,
            unsigned int attachment,
            unsigned int texture,
            int          level){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPixelStore.xhtml];
        void (*PixelStorei)(unsigned int oname, int param){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glProgramUniform.xhtml];
        void (*ProgramUniform4fv)(unsigned int program, int location, int count, const float *value){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glProgramUniform.xhtml];
        void (*ProgramUniformMatrix4fv)(
            unsigned int  program,
            int           location,
            int           count,
            unsigned char transpose,
            const float  *value){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glSamplerParameter.xhtml];
        void (*SamplerParameterf)(unsigned int sampler, unsigned int pname, float param){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glSamplerParameter.xhtml];
        void (*SamplerParameterfv)(unsigned int sampler, unsigned int pname, const float *params){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glSamplerParameter.xhtml];
        void (*SamplerParameterIiv)(unsigned int sampler, unsigned int pname, const int *params){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glSamplerParameter.xhtml];
        void (*SamplerParameterIuiv)(unsigned int sampler, unsigned int pname, const unsigned int *params){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glSamplerParameter.xhtml];
        void (*SamplerParameteri)(unsigned int sampler, unsigned int pname, int param){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glSamplerParameter.xhtml];
        void (*SamplerParameteriv)(unsigned int sampler, unsigned int pname, const int *params){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml];
        void (*ShaderSource)(unsigned int shader, int count, const char *const *string, const int *length){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml];
        void (*TextureParameteri)(unsigned int texture, unsigned int pname, int param){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexStorage2D.xhtml];
        void (*TextureStorage2D)(unsigned int texture, int levels, unsigned int internalformat, int width, int height){
            nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexSubImage2D.xhtml];
        void (*TextureSubImage2D)(
            unsigned int texture,
            int          level,
            int          xoffset,
            int          yoffset,
            int          width,
            int          height,
            unsigned int format,
            unsigned int type,
            const void  *pixels){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml];
        void (*UseProgram)(unsigned int program){nullptr};
        /// @brief see [https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml];
        void (*Viewport)(int x, int y, int width, int height){nullptr};

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