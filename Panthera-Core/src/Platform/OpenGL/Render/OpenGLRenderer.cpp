#include "OpenGLRenderer.hpp"

#include <glad/glad.h>

namespace Panthera
{

    OpenGLRenderer::OpenGLRenderer()
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    void OpenGLRenderer::Init()
    {
    }

    void OpenGLRenderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawIndexed(const Ref<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        vertexArray->GetIndexBuffer()->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}