#ifndef PANTHERA_OPENGLSHADER_HPP
#define PANTHERA_OPENGLSHADER_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Shader/Shader.hpp"

namespace Panthera
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const String& filepath);
        OpenGLShader(const std::initializer_list<const String> &src);
        ~OpenGLShader();
    };
}

#endif //PANTHERA_OPENGLSHADER_HPP
