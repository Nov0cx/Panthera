#include "IndexBuffer.hpp"

#include "Panthera/Core/Log.hpp"
#include "Panthera/Render/Renderer.hpp"

#include "Platform/OpenGL/Render/Buffer/OpenGLIndexBuffer.hpp"

namespace Panthera
{

    Ref <IndexBuffer> IndexBuffer::Create(const void *indicies, uint32_t count)
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLIndexBuffer>(indicies, count);
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan IndexBuffer is not supported yet!")
            case RendererAPI::None:
                ASSERT(false, "IndexBuffer without RendererAPI is not supported yet!")
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D IndexBuffer is not supported yet!")
            case RendererAPI::Metal:
                ASSERT(false, "Metal IndexBuffer is not supported yet!")
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES IndexBuffer is not supported yet!")
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)RendererState::GetAPI())
        }
    }
}
