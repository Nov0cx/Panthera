#ifndef PANTHERA_INDEXBUFFER_HPP
#define PANTHERA_INDEXBUFFER_HPP

#include <cinttypes>
#include "Panthera/Core/Pointer.hpp"

namespace Panthera
{
    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(const void* indicies, uint32_t count);

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() = 0;
    };
}

#endif //PANTHERA_INDEXBUFFER_HPP
