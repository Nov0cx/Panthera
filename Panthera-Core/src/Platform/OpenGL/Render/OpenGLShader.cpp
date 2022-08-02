#include "OpenGLShader.hpp"

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

#include "Panthera/Core/Log.hpp"

namespace Panthera
{

    OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        ASSERT(false, "NOT IMPLEMENTED YET!");
    }

    OpenGLShader::OpenGLShader(const std::string &path)
    {
        ASSERT(false, "NOT IMPLEMENTED YET!");
    }

    void OpenGLShader::Bind() const
    {
        ASSERT(false, "NOT IMPLEMENTED YET!");
    }

    void OpenGLShader::Unbind() const
    {
        ASSERT(false, "NOT IMPLEMENTED YET!");
    }

    RendererID OpenGLShader::GetRendererID() const
    {
        ASSERT(false, "NOT IMPLEMENTED YET!");
    }
}