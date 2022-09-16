#include "Buffer.hpp"

#ifdef PANTHERA_OPENGL
#include "Panthera/Platform/OpenGL/Buffer/OpenGLBuffer.hpp"
#endif

namespace Panthera
{

    uint32_t GetDataTypeSize(ShaderDataType type)
    {
#ifdef PANTHERA_OPENGL
        return GetDataTypeSizeOpenGL(type);
#else
        switch (type)
        {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
        }
#endif
    }

    Ref <IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLIndexBuffer>::Create(indices, count);
#else
        return nullptr;
#endif
    }

    Ref <VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLVertexBuffer>::Create(vertices, size);
#else
        return nullptr;
#endif
    }

    Ref <VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
#ifdef PANTHERA_OPENGL
        return Ref<OpenGLVertexBuffer>::Create(size);
#else
        return nullptr;
#endif
    }


}