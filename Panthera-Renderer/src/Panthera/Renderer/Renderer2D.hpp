#ifndef PANTHERA_RENDERER2D_HPP
#define PANTHERA_RENDERER2D_HPP

#include "ppch.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture2D.hpp"

namespace Panthera
{
    // fwd
    struct Renderer2DStorage;

    class Renderer2D
    {
    public:
        void Init();
        void Shutdown();

        void DrawTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color);
        void DrawTriangle(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec4 &color);
        void DrawTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
        void DrawTriangle(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec4 &color, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
        void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color);
        void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);

        void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color);
        void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color);
        void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
        void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
        void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color);
        void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);

        void DrawIndexed(uint32_t count);
        void Flush();

    private:
        void InitTriangle(Ref<Shader> &shader);
        void InitQuad(Ref<Shader> &shader);
    private:
        Renderer2DStorage* m_Storage;
    };
}

#endif //PANTHERA_RENDERER2D_HPP
