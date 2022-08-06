#include "UniformBuffer.hpp"

#include "Panthera/Core/Log.hpp"
#include "Panthera/Render/Renderer.hpp"

#include "Platform/OpenGL/Render/Shader/OpenGLUniformBuffer.hpp"

namespace Panthera
{

    Ref <UniformBuffer> UniformBuffer::Create(size_t size, uint32_t binding)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLUniformBuffer>(size, binding);
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan UniformBuffer is not supported yet!");
            case RendererAPI::None:
                ASSERT(false, "UniformBuffer without RendererAPI is not supported yet!");
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D UniformBuffer is not supported yet!");
            case RendererAPI::Metal:
                ASSERT(false, "Metal UniformBuffer is not supported yet!");
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES UniformBuffer is not supported yet!");
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)Renderer::GetAPI());
        }
    }
}