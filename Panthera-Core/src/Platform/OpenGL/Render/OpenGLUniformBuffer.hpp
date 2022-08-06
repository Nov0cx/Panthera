#ifndef PANTHERA_OPENGLUNIFORMBUFFER_HPP
#define PANTHERA_OPENGLUNIFORMBUFFER_HPP

#include "Panthera/Render/UniformBuffer.hpp"
#include "Panthera/Render/RenderAPI.hpp"

namespace Panthera
{
    class OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        OpenGLUniformBuffer(size_t size, uint32_t binding);
        virtual void SetData(const void* data, size_t size, uint32_t offset = 0) override;
    private:
        RendererID m_RendererID;
    };
}

#endif //PANTHERA_OPENGLUNIFORMBUFFER_HPP
