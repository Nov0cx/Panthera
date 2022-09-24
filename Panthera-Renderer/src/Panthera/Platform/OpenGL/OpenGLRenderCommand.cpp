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
}


