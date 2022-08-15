#include "Framebuffer.hpp"

#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Core/Log.hpp"

#include "Platform/OpenGL/Render/Framebuffer/OpenGLFramebuffer.hpp"

namespace Panthera
{

    Ref <Framebuffer> Framebuffer::Create(const std::initializer_list <FramebufferAttachmentSpecification> &attachments)
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLFramebuffer>(attachments);
            case RendererAPI::Vulkan:
                ASSERT(false, "Vulkan Framebuffer not implemented yet")
            case RendererAPI::None:
                ASSERT(false, "No RendererAPI selected")
            case RendererAPI::Direct3D:
                ASSERT(false, "Direct3D Framebuffer not implemented yet")
            case RendererAPI::Metal:
                ASSERT(false, "Metal Framebuffer not implemented yet")
            case RendererAPI::OpenGLES:
                ASSERT(false, "OpenGLES Framebuffer not implemented yet")
            default:
                    ASSERT(false, "Unknown RendererAPI")
        }
    }
}