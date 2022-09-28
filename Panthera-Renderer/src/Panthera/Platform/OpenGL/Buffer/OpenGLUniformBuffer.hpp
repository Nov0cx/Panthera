#ifndef PANTHERA_OPENGLUNIFORMBUFFER_HPP
#define PANTHERA_OPENGLUNIFORMBUFFER_HPP

#include "ppch.hpp"
#include "Panthera/Renderer/Buffer/UniformBuffer.hpp"

namespace Panthera
{
    class PT_API OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        using RendererID = uint32_t;
    public:
        OpenGLUniformBuffer(size_t size, uint32_t binding);
        virtual void SetData(const void* data, size_t size, uint32_t offset = 0) override;

    private:
        RendererID m_RendererID;
    };
}

#endif //PANTHERA_OPENGLUNIFORMBUFFER_HPP
