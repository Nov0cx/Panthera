#ifndef PANTHERA_OPENGLRENDERER_HPP
#define PANTHERA_OPENGLRENDERER_HPP

#include "Panthera/Render/Renderer.hpp"

namespace Panthera
{
    struct RendererData;
    struct QuadVertex;
    struct CircleVertex;
    struct TriangleVertex;
    struct LineVertex;

    class OpenGLRenderer : public Renderer
    {
    public:
        OpenGLRenderer() = default;
        virtual ~OpenGLRenderer() = default;
        virtual void Init() override;
        virtual void Clear(glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f)) override;
        virtual void DrawIndexed(uint32_t count) override;

        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;

        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;

        virtual void DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness, float fade) override;
        virtual void DrawCircle(const glm::vec2 &center, const glm::vec4 &color, float radius, float borderThickness, float fade) override;
        virtual void DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness, float fade, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawCircle(const glm::vec2 &center, const glm::vec4 &color, float radius, float borderThickness, float fade, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness, float fade) override;
        virtual void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness, float fade, float tiling, Ref<Texture2D> &texture) override;

        virtual void DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color, float thickness) override;

        virtual void BeginScene() override;
        virtual void BeginScene(OrthographicCamera &camera) override;
        virtual void EndScene() override;
        virtual void Flush() override;

    private:
        RendererData *m_Data = nullptr;
        void InitQuad();
        void InitCircle();
        void InitTriangle();
        void InitLine();
    };
}

#endif //PANTHERA_OPENGLRENDERER_HPP
