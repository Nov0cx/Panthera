#include "Renderer.hpp"

namespace Panthera {

    static RendererAPI::API s_API = RendererAPI::API::OpenGL;

    RendererAPI::API RendererAPI::GetAPI()
    {
        return s_API;
    }

    RendererAPI::API RendererAPI::SetAPI(RendererAPI::API api)
    {
        s_API = api;
    }


}