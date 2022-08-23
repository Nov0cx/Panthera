#ifndef PANTHERA_RENDERER_HPP
#define PANTHERA_RENDERER_HPP

#include "RenderAPI.hpp"
#include <glm/glm.hpp>
#include "VertexArray/VertexArray.hpp"
#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/OrthographicCamera.hpp"
#include "Framebuffer/Framebuffer.hpp"

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
        static Renderer* Create();

#pragma section("Core")
        virtual void Init() = 0;
        virtual void Clear(glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f)) = 0;
        virtual void DrawIndexed(uint32_t count) = 0;

#pragma section("Quad")

        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color) = 0;
        virtual void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;

#pragma section("Triangle")

        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) = 0;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) = 0;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) = 0;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color) = 0;
        virtual void DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color) = 0;
        virtual void DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref<Texture2D> &texture) = 0;

#pragma section("Circle")

        virtual void DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness, float fade) = 0;
        virtual void DrawCircle(const glm::vec2 &center, const glm::vec4 &color, float radius, float borderThickness, float fade) = 0;
        virtual void DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness, float fade, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawCircle(const glm::vec2 &center, const glm::vec4 &color, float radius, float borderThickness, float fade, float tiling, Ref<Texture2D> &texture) = 0;
        virtual void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness, float fade) = 0;
        virtual void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness, float fade, float tiling, Ref<Texture2D> &texture) = 0;

#pragma section("Line")
        virtual void DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color, float thickness) = 0;

#pragma section("Scene")

        virtual void BeginScene() = 0;
        virtual void BeginScene(OrthographicCamera &camera) = 0;
        virtual void EndScene() = 0;
        virtual void Flush() = 0;
        virtual Ref<Framebuffer> GetFramebuffer() = 0;

    };
}

#endif //PANTHERA_RENDERER_HPP
