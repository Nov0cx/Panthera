#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

#include "RenderAPI.hpp"
#include <glm/glm.hpp>
#include "VertexArray/VertexArray.hpp"

namespace Panthera
{

    class RendererState
    {
    public:
        static RendererAPI GetAPI();
        static void SetAPI(RendererAPI api);
    };

    class Renderer
    {
    public:
        static Renderer* CreateRenderer();
        virtual void Init() = 0;
        virtual void Clear(glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f)) = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
    };
}

#endif //PANTHERA_RENDERER_HPP
