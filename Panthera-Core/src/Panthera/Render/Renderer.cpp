#include "Renderer.hpp"

#include "Panthera/Core/Log.hpp"
#include "Platform/OpenGL/Render/OpenGLRenderer.hpp"

namespace Panthera
{

    static RendererAPI s_API = RendererAPI::OpenGL;

    RendererAPI RendererState::GetAPI()
    {
        return s_API;
    }

    void RendererState::SetAPI(RendererAPI api)
    {
        s_API = api;
    }

    Renderer *Renderer::Create()
    {
        switch (s_API)
        {
            case RendererAPI::OpenGL:
                return new OpenGLRenderer();
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
        }
        ASSERT(false, "Unknown RendererAPI!");
    }
}