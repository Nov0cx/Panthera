#ifndef PANTHERA_OPENGLVERTEXARRAY_HPP
#define PANTHERA_OPENGLVERTEXARRAY_HPP

#include "Panthera/Render/VertexArray/VertexArray.hpp"
#include "Panthera/Render/RenderAPI.hpp"

#include <vector>

namespace Panthera
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const override;
    private:
        RendererID m_RendererID;
        uint32_t m_VertexBufferCount = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}

#endif //PANTHERA_OPENGLVERTEXARRAY_HPP
