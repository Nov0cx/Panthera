#ifndef PANTHERA_BUFFER_HPP
#define PANTHERA_BUFFER_HPP

#include "ppch.hpp"

namespace Panthera
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    uint32_t GetDataTypeSize(ShaderDataType type);

    class VertexBufferLayout
    {
    public:
        struct Element
        {
            ShaderDataType Type;
            String Name;
            bool Normalized;
            uint32_t Size;
            uint32_t Offset;
            uint32_t Divisor;

            Element(ShaderDataType type, const String& name, bool normalized = false, uint32_t divisor = 0)
                    : Type(type), Name(name), Normalized(normalized), Size(GetDataTypeSize(type)), Offset(0), Divisor(divisor)
            {}

            uint32_t GetCount() const
            {
                switch (Type)
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
                }
                return 0;
            }
        };
    public:

        VertexBufferLayout() = default;
        VertexBufferLayout(const std::initializer_list<Element>& elements)
            : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<Element>& GetElements() const { return m_Elements; }
        inline uint32_t GetStride() const { return m_Stride; }

        std::vector<Element>::iterator begin() { return m_Elements.begin(); }
        std::vector<Element>::iterator end() { return m_Elements.end(); }
        std::vector<Element>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<Element>::const_iterator end() const { return m_Elements.end(); }

        void AddElement(ShaderDataType type, const String& name, bool normalized = false, uint32_t divisor = 0)
        {
            m_Elements.push_back({ type, name, normalized, divisor });
            CalculateOffsetsAndStride();
        }

        void AddElement(const Element& element)
        {
            m_Elements.push_back(element);
            CalculateOffsetsAndStride();
        }

        void AddElements(const std::initializer_list<Element>& elements)
        {
            m_Elements.insert(m_Elements.end(), elements.begin(), elements.end());
            CalculateOffsetsAndStride();
        }

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

    private:
        std::vector<Element> m_Elements;
        uint32_t m_Stride = 0;
    };

    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;
    };

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
        static Ref<VertexBuffer> Create(uint32_t size);
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(void* data, size_t size) = 0;
        virtual void SetBufferLayout(VertexBufferLayout layout) = 0;
        virtual VertexBufferLayout& GetLayout() = 0;
        virtual const VertexBufferLayout& GetLayout() const = 0;
    };
}

#endif //PANTHERA_BUFFER_HPP
