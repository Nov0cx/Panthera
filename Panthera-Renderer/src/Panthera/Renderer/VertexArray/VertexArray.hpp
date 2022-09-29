#ifndef PANTHERA_VERTEXARRAY_HPP
#define PANTHERA_VERTEXARRAY_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Buffer/Buffer.hpp"

namespace Panthera
{
    class VertexArray
    {
    public:
        static Ref<VertexArray> Create();
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
        virtual const Ref<IndexBuffer> GetIndexBuffer() const = 0;
    };
}

#endif //PANTHERA_VERTEXARRAY_HPP
