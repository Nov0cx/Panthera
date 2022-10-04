#include "RenderCommands.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/OpenGLRenderCommand.hpp"
#endif

namespace Panthera
{

    void RenderCommand::DrawIndexed(uint32_t count)
    {
#ifdef PANTHERA_OPENGL
        OpenGLRenderCommand::DrawIndexed(count);
#endif
    }

    void RenderCommand::Clear(const glm::vec4 &color)
    {
#ifdef PANTHERA_OPENGL
        OpenGLRenderCommand::Clear(color);
#endif
    }

    void RenderCommand::EnableBlending()
    {
#ifdef PANTHERA_OPENGL
        OpenGLRenderCommand::EnableBlending();
#endif
    }

    void RenderCommand::SetViewport(const glm::vec4 &viewport)
    {
#ifdef PANTHERA_OPENGL
        OpenGLRenderCommand::SetViewport(viewport);
#endif
    }
}