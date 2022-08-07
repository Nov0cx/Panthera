#include "VertexBuffer.hpp"

#include "Panthera/Core/Log.hpp"
#include "Panthera/Render/Renderer.hpp"

#include "Platform/OpenGL/Render/Buffer/OpenGLVertexBuffer.hpp"

namespace Panthera
{

    Ref <VertexBuffer> VertexBuffer::Create(const void *data, size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(data, size);
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan VertexBuffer is not supported yet!");
            case RendererAPI::None:
                ASSERT(false, "VertexBuffer without RendererAPI is not supported yet!");
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D VertexBuffer is not supported yet!");
            case RendererAPI::Metal:
                ASSERT(false, "Metal VertexBuffer is not supported yet!");
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES VertexBuffer is not supported yet!");
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)Renderer::GetAPI());
        }
    }

    uint32_t GetDataTypeSize(ShaderDataType type)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return GetDataTypeSizeOpenGL(type);
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan data type size is not supported yet!")
            case RendererAPI::None:
                ASSERT(false, "Data type size without RendererAPI is not supported yet!")
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D data type size is not supported yet!")
            case RendererAPI::Metal:
                ASSERT(false, "Metal data type size is not supported yet!")
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES data type size is not supported yet!")
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)Renderer::GetAPI())
        }
    }

    Ref <VertexBuffer> VertexBuffer::Create(size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(size);
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan VertexBuffer is not supported yet!")
            case RendererAPI::None:
                ASSERT(false, "VertexBuffer without RendererAPI is not supported yet!")
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D VertexBuffer is not supported yet!")
            case RendererAPI::Metal:
                ASSERT(false, "Metal VertexBuffer is not supported yet!")
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES VertexBuffer is not supported yet!")
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int)Renderer::GetAPI())
        }
    }

    VertexBufferLayout::VertexBufferLayout(const std::initializer_list <VertexLayout> &layouts)
    {
        for (auto& layoutItem : layouts)
        {
            m_Layouts.push_back(layoutItem);
        }

        Init();
    }

    VertexBufferLayout::VertexBufferLayout()
    {
        Init();
    }
}