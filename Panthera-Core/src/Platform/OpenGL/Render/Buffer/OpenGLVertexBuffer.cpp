#include "OpenGLVertexBuffer.hpp"

#include "Panthera/Core/Log.hpp"

namespace Panthera
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void *data, size_t size)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
    {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetBufferLayout(VertexBufferLayout layout)
    {
        m_Layout = layout;
    }

    VertexBufferLayout &OpenGLVertexBuffer::GetLayout()
    {
        return m_Layout;
    }

    void OpenGLVertexBuffer::AddData(void *data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    const VertexBufferLayout &OpenGLVertexBuffer::GetLayout() const
    {
        return m_Layout;
    }


    uint32_t GetDataTypeSizeOpenGL(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
                return sizeof(GLfloat);
            case ShaderDataType::Float2:
                return sizeof(GLfloat) * 2;
            case ShaderDataType::Float3:
                return sizeof(GLfloat) * 3;
            case ShaderDataType::Float4:
                return sizeof(GLfloat) * 4;
            case ShaderDataType::Int:
                return sizeof(GLint);
            case ShaderDataType::Int2:
                return sizeof(GLint) * 2;
            case ShaderDataType::Int3:
                return sizeof(GLint) * 3;
            case ShaderDataType::Int4:
                return sizeof(GLint) * 4;
            case ShaderDataType::Mat3:
                return sizeof(GLfloat) * 3 * 3;
            case ShaderDataType::Mat4:
                return sizeof(GLfloat) * 4 * 4;
            case ShaderDataType::Bool:
                return sizeof(GLboolean);
        }

        ASSERT(false, "Unsupported BufferLayoutType. {}", (int) type);
    }
}