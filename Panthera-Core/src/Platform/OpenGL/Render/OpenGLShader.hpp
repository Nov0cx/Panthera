#ifndef PANTHERA_OPENGLSHADER_HPP
#define PANTHERA_OPENGLSHADER_HPP

#include "Panthera/Render/Shader.hpp"
#include "Panthera/Core/Pointer.hpp"
#include <string>
#include "Panthera/Render/RenderAPI.hpp"
#include <unordered_map>
#include <vector>

namespace Panthera
{
    // fwd
    struct ShaderSrc;

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        OpenGLShader(const std::string &path);

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual RendererID GetRendererID() const override;

    private:
        RendererID m_RendererID;
        std::string m_Name;
        std::unordered_map<uint32_t, std::vector<uint32_t>> m_VulkanBinary;
        std::unordered_map<uint32_t, std::vector<uint32_t>> m_OpenGLBinary;

        std::unordered_map<uint32_t, std::string> m_OpenGLSrc;
    private:
        void CompileOrGetVulkanBinaryForOpenGL(std::vector<ShaderSrc>& srcs);
        void CompileOrGetShaders();
        void CreateProgram();
    };
}

#endif //PANTHERA_OPENGLSHADER_HPP
