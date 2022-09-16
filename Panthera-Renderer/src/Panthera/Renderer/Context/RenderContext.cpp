#include "RenderContext.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/OpenGLRenderContext.hpp"
#endif

namespace Panthera
{

    Ref <RenderContext> RenderContext::Create(void* nativeWindow)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLRenderContext>::Create(nativeWindow);
#else
        return nullptr;
#endif
    }
}