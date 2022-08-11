#ifndef PANTHERA_OPENGLRENDERER_HPP
#define PANTHERA_OPENGLRENDERER_HPP

#include "Panthera/Render/Renderer.hpp"

namespace Panthera
{
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
        virtual void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;

        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;
        virtual void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color) override;
        virtual void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) override;

        virtual void BeginScene() override;
        virtual void BeginScene(OrthographicCamera &camera) override;
        virtual void EndScene() override;
        virtual void Flush() override;
    };
}

#endif //PANTHERA_OPENGLRENDERER_HPP
