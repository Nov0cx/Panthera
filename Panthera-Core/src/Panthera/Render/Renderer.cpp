#include "Renderer.hpp"

namespace Panthera {

    static RendererAPI s_API = RendererAPI::OpenGL;

    RendererAPI Renderer::GetAPI()
    {
        return s_API;
    }

    void Renderer::SetAPI(RendererAPI api)
    {
        s_API = api;
    }
}