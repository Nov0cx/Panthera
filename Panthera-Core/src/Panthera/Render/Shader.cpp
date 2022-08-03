#include "Shader.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/Render/OpenGLShader.hpp"
#include "Panthera/Core/Log.hpp"

namespace Panthera
{
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;

    Ref <Shader> Shader::Create(const std::string &path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLShader>(path);
            case RendererAPI::Vulkan:
                LOG_WARN("Vulkan Shader is not supported yet!");
                break;
            case RendererAPI::None:
                LOG_WARN("Shader with RendererAPI is not supported yet!");
                break;
            case RendererAPI::Direct3D:
                LOG_WARN("Direct3D Shader is not supported yet!");
                break;
            case RendererAPI::Metal:
                LOG_WARN("Metal Shader is not supported yet!");
                break;
            case RendererAPI::OpenGLES:
                LOG_WARN("OpenGLES Shader is not supported yet!");
                break;
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)Renderer::GetAPI());
        }

        ASSERT(false, "Not Supported RendererAPI")

    }

    Ref <Shader> Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
    {

        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
            case RendererAPI::Vulkan:
                LOG_WARN("Vulkan Shader is not supported yet!");
                break;
            case RendererAPI::None:
                LOG_WARN("Shader with RendererAPI is not supported yet!");
                break;
            case RendererAPI::Direct3D:
                LOG_WARN("Direct3D Shader is not supported yet!");
                break;
            case RendererAPI::Metal:
                LOG_WARN("Metal Shader is not supported yet!");
                break;
            case RendererAPI::OpenGLES:
                LOG_WARN("OpenGLES Shader is not supported yet!");
                break;
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)Renderer::GetAPI());
        }

        ASSERT(false, "Not Supported RendererAPI")

    }

    Ref <Shader> ShaderLibrary::CreateShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        return m_Shaders[name] = Shader::Create(name, vertexSrc, fragmentSrc);
    }

    Ref <Shader> ShaderLibrary::CreateShader(const std::string &name, const std::string &path)
    {
        return m_Shaders[name] = Shader::Create(path);
    }

    Ref <Shader> ShaderLibrary::GetShader(const std::string &name)
    {
        return m_Shaders[name];
    }
}