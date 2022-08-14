#include "Texture.hpp"

#include "Panthera/Core/Log.hpp"
#include "Panthera/Render/Renderer.hpp"
#include "Platform/OpenGL/Render/Texture/OpenGLTexture.hpp"

namespace Panthera
{

    Ref <Texture2D> Texture2D::Create(const Texture2DSpecification& spec)
    {
        switch (RendererState::GetAPI())
        {
            case RendererAPI::OpenGL:
                return CreateRef<OpenGLTexture2D>(spec);
            case RendererAPI::None:
                ASSERT(false, "RendererAPI::None is not supported!");
            case RendererAPI::Vulkan:
                ASSERT(false, "RendererAPI::Vulkan is not supported!");
            case RendererAPI::Direct3D:
                ASSERT(false, "RendererAPI::Direct3D is not supported!");
            case RendererAPI::Metal:
                ASSERT(false, "RendererAPI::Metal is not supported!");
            case RendererAPI::OpenGLES:
                ASSERT(false, "RendererAPI::OpenGLES is not supported!");
            default:
                ASSERT(false, "Unknown RendererAPI!");
        }
    }

}