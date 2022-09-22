#ifndef PANTHERA_OPENGLBUFFER_HPP
#define PANTHERA_OPENGLBUFFER_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Buffer/Buffer.hpp"

namespace Panthera
{
    uint32_t GetDataTypeSizeOpenGL(ShaderDataType type);

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);

        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;

        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override;

    private:
        RendererID m_RendererID;
        uint32_t m_Count;
    };

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLVertexBuffer(const void *data, size_t size);

        OpenGLVertexBuffer(size_t size);

        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;

        virtual void Unbind() const override;

        virtual void SetBufferLayout(VertexBufferLayout layout) override;

        virtual VertexBufferLayout &GetLayout() override;

        virtual const VertexBufferLayout &GetLayout() const override;

        virtual void SetData(void *data, size_t size) override;

    private:
        RendererID m_RendererID;
        VertexBufferLayout m_Layout;
    };
}

#endif //PANTHERA_OPENGLBUFFER_HPP
