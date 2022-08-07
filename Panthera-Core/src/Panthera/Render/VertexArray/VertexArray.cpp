#include "VertexArray.hpp"

#include "Panthera/Core/Log.hpp"
#include "Panthera/Render/Renderer.hpp"

#include "Platform/OpenGL/Render/VertexArray/OpenGLVertexArray.hpp"

namespace Panthera
{

    Ref <VertexArray> VertexArray::Create()
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLVertexArray>();
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan VertexArray is not supported yet!")
            case RendererAPI::None:
                ASSERT(false, "VertexArray without RendererAPI is not supported yet!")
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D VertexArray is not supported yet!")
            case RendererAPI::Metal:
                ASSERT(false, "Metal VertexArray is not supported yet!")
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES VertexArray is not supported yet!")
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)RendererState::GetAPI())
        }
    }
}