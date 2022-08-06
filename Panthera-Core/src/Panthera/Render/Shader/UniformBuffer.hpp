#ifndef PANTHERA_UNIFORMBUFFER_HPP
#define PANTHERA_UNIFORMBUFFER_HPP

#include <cstdint>
#include "Panthera/Core/Pointer.hpp"

namespace Panthera
{
    class UniformBuffer
    {
    public:
        static Ref<UniformBuffer> Create(size_t size, uint32_t binding);

        virtual void SetData(const void* data, size_t size, uint32_t offset = 0) = 0;
    };
}

#endif //PANTHERA_UNIFORMBUFFER_HPP
