#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

#include "RenderAPI.hpp"

namespace Panthera
{

    class Renderer
    {
    public:
        static RendererAPI GetAPI();
        static void SetAPI(RendererAPI api);
    private:
        Renderer() = default;
    };
}

#endif //PANTHERA_RENDERER_HPP
