#ifndef PANTHERA_VERTEXBUFFER_HPP
#define PANTHERA_VERTEXBUFFER_HPP

#include "Panthera/Core/Pointer.hpp"
#include <cstdint>

#include <vector>
#include <initializer_list>
#include <string>

namespace Panthera
{
    enum class ShaderDataType
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    uint32_t GetDataTypeSize(ShaderDataType type);

    struct VertexLayout
    {
        std::string Name;
        ShaderDataType DataType;
        bool Normalized;
        uint32_t Size;
        uint32_t Offset;

        VertexLayout(std::string name, ShaderDataType dataType, bool normalised = false)
                : Name(std::move(name)), DataType(dataType), Normalized(normalised), Size(GetDataTypeSize(dataType)),
                  Offset(0)
        {}

        inline uint8_t GetCount() const
        {
            switch (DataType)
            {
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 3;
                case ShaderDataType::Mat4:
                    return 4;
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
                case ShaderDataType::None:
                    return 0;
            }
        }
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout();
        VertexBufferLayout(const std::initializer_list <VertexLayout> &layouts);

        ~VertexBufferLayout() = default;

        [[nodiscard]] inline const std::vector <VertexLayout> &GetLayouts() const
        { return m_Layouts; }
        [[nodiscard]] inline uint32_t GetStride() const
        { return m_Stride; }
        std::vector<VertexLayout>::iterator begin()
        { return m_Layouts.begin(); }
        std::vector<VertexLayout>::iterator end()
        { return m_Layouts.end(); }
        [[nodiscard]] std::vector<VertexLayout>::const_iterator begin() const
        { return m_Layouts.begin(); }
        [[nodiscard]] std::vector<VertexLayout>::const_iterator end() const
        { return m_Layouts.end(); }

    private:
        void Init()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto &layoutItem: m_Layouts)
            {
                layoutItem.Offset = offset;
                offset += layoutItem.Size;
                m_Stride += layoutItem.Size;
            }
        }

    private:
        std::vector <VertexLayout> m_Layouts;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer
    {
    public:
        static Ref <VertexBuffer> Create(const void *vertices, size_t size);
        static Ref <VertexBuffer> Create(size_t size);

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddData(void *data, size_t size) = 0;

        virtual void SetBufferLayout(VertexBufferLayout layout) = 0;
        virtual VertexBufferLayout& GetLayout() = 0;
        virtual const VertexBufferLayout& GetLayout() const = 0;
    };
}

#endif //PANTHERA_VERTEXBUFFER_HPP
