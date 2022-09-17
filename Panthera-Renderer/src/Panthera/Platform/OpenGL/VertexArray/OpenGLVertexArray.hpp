#ifndef PANTHERA_OPENGLVERTEXARRAY_HPP
#define PANTHERA_OPENGLVERTEXARRAY_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/VertexArray/VertexArray.hpp"

namespace Panthera
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        RendererID m_RendererID;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
        uint32_t m_VertexBufferIndex = 0;
    };
}

#endif //PANTHERA_OPENGLVERTEXARRAY_HPP
