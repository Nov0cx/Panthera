#ifndef PANTHERA_OPENGLINDEXBUFFER_HPP
#define PANTHERA_OPENGLINDEXBUFFER_HPP

#include "Panthera/Render/Buffer/IndexBuffer.hpp"
#include "Panthera/Render/RenderAPI.hpp"

namespace Panthera
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const void *indicies, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() override;

    private:
        RendererID m_RendererID;
        uint32_t m_Count;
    };
}

#endif //PANTHERA_OPENGLINDEXBUFFER_HPP
