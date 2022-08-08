#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

#include "RenderAPI.hpp"
#include <glm/glm.hpp>
#include "VertexArray/VertexArray.hpp"
#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"

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
        virtual void DrawQuad(glm::vec3 center, glm::vec2 size, glm::vec4 color) = 0;
        virtual void DrawQuad(glm::vec2 center, glm::vec2 size, glm::vec4 color) = 0;
        virtual void DrawQuad(glm::vec3 center, glm::vec2 size, glm::vec4 color, uint8_t index, Ref<Texture2D> &texture) = 0;
        virtual void DrawQuad(glm::vec2 center, glm::vec2 size, glm::vec4 color, uint8_t index, Ref<Texture2D> &texture) = 0;
    };
}

#endif //PANTHERA_RENDERER_HPP
