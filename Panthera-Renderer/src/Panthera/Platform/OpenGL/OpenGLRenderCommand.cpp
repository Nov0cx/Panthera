#include "OpenGLRenderCommand.hpp"

#include <glad/glad.h>

namespace Panthera
{
    void OpenGLRenderCommand::DrawIndexed(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderCommand::Clear(const glm::vec4 &color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderCommand::EnableBlending()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderCommand::SetViewport(const glm::vec4 &viewport)
    {
        glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
    }
}


