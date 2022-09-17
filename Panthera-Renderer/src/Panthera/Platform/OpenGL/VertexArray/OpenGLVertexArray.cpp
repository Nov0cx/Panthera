#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

namespace Panthera
{
    static GLenum GetOpenGLDataType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Bool:
                return GL_INT;
        }

        PT_ASSERT(false, "Unsupported ShaderDataType. {}", (int) type);
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
        if (m_IndexBuffer)
        {
            m_IndexBuffer->Bind();
        }
        for (auto& buffer : m_VertexBuffers)
        {
            buffer->Bind();
        }
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref <VertexBuffer> &vertexBuffer)
    {
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
                                  element.GetCount(),
                                  GetOpenGLDataType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *) element.Offset);
            m_VertexBufferIndex++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref <IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}