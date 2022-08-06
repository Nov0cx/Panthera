#include "OpenGLUniformBuffer.hpp"

namespace Panthera
{

    OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size, uint32_t binding)
    {
        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
    }

    void OpenGLUniformBuffer::SetData(const void *data, size_t size, uint32_t offset)
    {
        glNamedBufferSubData(m_RendererID, offset, size, data);
    }
}