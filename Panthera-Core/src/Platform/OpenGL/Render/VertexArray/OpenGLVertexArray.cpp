#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>
#include "Panthera/Core/Log.hpp"

namespace Panthera
{

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
        m_IndexBuffer->Bind();
        for (auto& buffer : m_Buffers)
        {
            buffer->Bind();
        }
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }


    static GLenum GetOpenGLLayoutType(ShaderDataType type)
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

        ASSERT(false, "Unsupported ShaderDataType. {}", (int) type);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref <VertexBuffer> &buffer)
    {
        ASSERT(!buffer->GetLayout().GetLayouts().empty(), "Vertex buffer has no layout");
        Bind();
        buffer->Bind();

        auto bufferLayout = buffer->GetLayout();
        for (const auto &layout: bufferLayout.GetLayouts())
        {
            switch (layout.DataType)
            {

                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(m_VertexBufferCount);
                    glVertexAttribPointer(m_VertexBufferCount,
                                          layout.GetCount(),
                                          GetOpenGLLayoutType(layout.DataType),
                                          layout.Normalized ? GL_TRUE : GL_FALSE,
                                          bufferLayout.GetStride(),
                                          reinterpret_cast<const void *>(layout.Offset));
                    m_VertexBufferCount++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                {
                    glEnableVertexAttribArray(m_VertexBufferCount);
                    glVertexAttribIPointer(m_VertexBufferCount,
                                           layout.GetCount(),
                                           GetOpenGLLayoutType(layout.DataType),
                                           bufferLayout.GetStride(),
                                           reinterpret_cast<const void *>(layout.Offset));
                    m_VertexBufferCount++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint8_t count = layout.GetCount();
                    for (uint8_t i = 0; i < count; i++)
                    {
                        glEnableVertexAttribArray(m_VertexBufferCount);
                        glVertexAttribPointer(m_VertexBufferCount,
                                              count,
                                              GetOpenGLLayoutType(layout.DataType),
                                              layout.Normalized ? GL_TRUE : GL_FALSE,
                                              bufferLayout.GetStride(),
                                              (const void*)(layout.Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(m_VertexBufferCount, 1);
                        m_VertexBufferCount++;
                    }
                    break;
                }
                case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(m_VertexBufferCount);
                    glVertexAttribIPointer(m_VertexBufferCount,
                                           layout.GetCount(),
                                           GetOpenGLLayoutType(layout.DataType),
                                           bufferLayout.GetStride(),
                                           reinterpret_cast<const void *>(layout.Offset));
                    m_VertexBufferCount++;
                    break;
                }
            }
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref <IndexBuffer> &buffer)
    {
        m_IndexBuffer = buffer;
    }

    const Ref <IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }


    const std::vector<Ref<VertexBuffer>> &OpenGLVertexArray::GetVertexBuffers() const
    {
        return m_VertexBuffers;
    }
}