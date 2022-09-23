#include "UniformBuffer.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/Buffer/OpenGLUniformBuffer.hpp"
#endif

namespace Panthera
{

    Ref <UniformBuffer> UniformBuffer::Create(size_t size, uint32_t binding)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLUniformBuffer>::Create(size, binding);
#else
        return nullptr;
#endif

    }
}