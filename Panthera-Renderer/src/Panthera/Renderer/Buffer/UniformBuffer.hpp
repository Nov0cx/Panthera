#ifndef PANTHERA_UNIFORMBUFFER_HPP
#define PANTHERA_UNIFORMBUFFER_HPP

#include "ppch.hpp"

namespace Panthera
{
    class PT_API UniformBuffer
    {
    public:
        static Ref<UniformBuffer> Create(size_t size, uint32_t binding);
    public:
        virtual void SetData(const void *data, size_t size, uint32_t offset = 0) = 0;
    };
}

#endif //PANTHERA_UNIFORMBUFFER_HPP
