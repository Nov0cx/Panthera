#include "RenderContext.hpp"

#include "Platform/OpenGL/Window/OpenGLRenderContext.hpp"

#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Core/Log.hpp"

namespace Panthera
{

    Ref <RenderContext> RenderContext::Create(std::any nativeWindow)
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLRenderContext>(nativeWindow);
            case RendererAPI::Vulkan:
                LOG_WARN("Vulkan Render Context is not supported yet!");
                break;
            case RendererAPI::None:
                LOG_WARN("Render Context with RendererAPI None is not supported yet!");
                break;
            case RendererAPI::Direct3D:
                LOG_WARN("Direct3D Render Context is not supported yet!");
                break;
            case RendererAPI::Metal:
                LOG_WARN("Metal Render Context is not supported yet!");
                break;
            case RendererAPI::OpenGLES:
                LOG_WARN("OpenGLES Render Context is not supported yet!");
                break;
            default:
                ASSERT(false, "Unknown RendererAPI! {}", (int) RendererState::GetAPI());
        }

        ASSERT(false, "Not Supported RendererAPI")
    }
}