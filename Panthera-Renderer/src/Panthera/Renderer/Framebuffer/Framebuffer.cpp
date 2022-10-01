#include "Framebuffer.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/Framebuffer/OpenGLFramebuffer.hpp"
#endif

namespace Panthera
{

    Ref <Framebuffer> Framebuffer::Create(const FramebufferInfo &info)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLFramebuffer>::Create(info);
#endif
    }
}