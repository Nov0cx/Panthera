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
    };
}

#endif //PANTHERA_OPENGLRENDERER_HPP
