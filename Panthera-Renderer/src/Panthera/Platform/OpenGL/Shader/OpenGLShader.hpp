#ifndef PANTHERA_OPENGLSHADER_HPP
#define PANTHERA_OPENGLSHADER_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Shader/Shader.hpp"

namespace Panthera
{
    class OpenGLShader : public Shader
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLShader(const String& filepath);
        OpenGLShader(const std::initializer_list<const String> &src);
        ~OpenGLShader();
    private:
        std::vector<Pair<uint32_t, String>> PreProcess(const String& source);
        void Compile(const Pair<uint32_t, String>& shader);
        void Link();

    private:
        RendererID m_RendererID;
        std::vector<Pair<uint32_t, std::vector<uint32_t>>> m_SpirV;
        std::vector<Pair<uint32_t, std::vector<uint32_t>>> m_OpenGLSpirV;
        std::vector<Pair<uint32_t, std::vector<String>>> m_OpenGLSrc;
    };
}

#endif //PANTHERA_OPENGLSHADER_HPP
