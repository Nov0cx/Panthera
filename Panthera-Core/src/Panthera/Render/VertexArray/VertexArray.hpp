#ifndef PANTHERA_VERTEXARRAY_HPP
#define PANTHERA_VERTEXARRAY_HPP

#include "Panthera/Core/Pointer.hpp"
#include "Panthera/Render/Buffer/VertexBuffer.hpp"
#include "Panthera/Render/Buffer/IndexBuffer.hpp"

#include <vector>

namespace Panthera
{
    class VertexArray
    {
    public:
        static Ref<VertexArray> Create();

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
    };
}

#endif //PANTHERA_VERTEXARRAY_HPP
