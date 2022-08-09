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
        virtual void DrawIndexed(uint32_t count) = 0;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void BeginScene() = 0;
        virtual void EndScene() = 0;
        virtual void Flush() = 0;
    };
}

#endif //PANTHERA_RENDERER_HPP
