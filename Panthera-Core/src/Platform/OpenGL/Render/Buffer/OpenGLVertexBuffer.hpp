#ifndef PANTHERA_OPENGLVERTEXBUFFER_HPP
#define PANTHERA_OPENGLVERTEXBUFFER_HPP

#include "Panthera/Render/Buffer/VertexBuffer.hpp"
#include "Panthera/Render/RenderAPI.hpp"

#include <glad/glad.h>

namespace Panthera
{
    uint32_t GetDataTypeSizeOpenGL(ShaderDataType type);

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const void *data, size_t size);
        OpenGLVertexBuffer(size_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetBufferLayout(VertexBufferLayout layout) override;
        virtual VertexBufferLayout& GetLayout() override;
        virtual const VertexBufferLayout& GetLayout() const override;

        virtual void AddData(void* data, size_t size) override;

    private:
        RendererID m_RendererID;
        VertexBufferLayout m_Layout;
    };
}

#endif //PANTHERA_OPENGLVERTEXBUFFER_HPP
