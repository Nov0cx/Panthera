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
        OpenGLShader(const String& filepath, const String& name);
        OpenGLShader(const String& name, const std::initializer_list<const String> &src);
        ~OpenGLShader();

        virtual void Bind() const override;
        virtual void* GetRenderObject() const override;
    private:
        void Handle(const std::vector<Pair<uint32_t, String>> &shaderSources);
        std::vector<Pair<uint32_t, String>> PreProcess(const String& source);
        void Compile(const Pair<uint32_t, String>& shader);
        void Link();

    private:
        RendererID m_RendererID;
        std::vector<Pair<uint32_t, std::vector<uint32_t>>> m_SpirV;
        std::vector<Pair<uint32_t, std::vector<uint32_t>>> m_OpenGLSpirV;
        String m_Name;
    };
}

#endif //PANTHERA_OPENGLSHADER_HPP
