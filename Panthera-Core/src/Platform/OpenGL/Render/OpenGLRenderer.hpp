#ifndef PANTHERA_OPENGLRENDERER_HPP
#define PANTHERA_OPENGLRENDERER_HPP

#include "Panthera/Render/Renderer.hpp"

namespace Panthera
{
    class OpenGLRenderer : public Renderer
    {
    public:
        OpenGLRenderer();
        virtual ~OpenGLRenderer();
        virtual void Init() override;
        virtual void Clear(glm::vec4 color = glm::vec4(0.f, 0.f, 0.f, 1.f)) override;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color) override;
        virtual void DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, uint8_t index, Ref<Texture2D> &texture) override;
        virtual void DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, uint8_t index, Ref<Texture2D> &texture) override;
    };
}

#endif //PANTHERA_OPENGLRENDERER_HPP
