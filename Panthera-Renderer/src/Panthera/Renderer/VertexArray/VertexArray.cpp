#include "VertexArray.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/VertexArray/OpenGLVertexArray.hpp"
#endif

namespace Panthera
{

    Ref <VertexArray> VertexArray::Create()
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLVertexArray>::Create();
#else
        return nullptr;
#endif
    }
}