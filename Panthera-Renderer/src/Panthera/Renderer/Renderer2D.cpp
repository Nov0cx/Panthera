#include "Renderer2D.hpp"

#include "RenderCommands.hpp"
#include "Panthera/RenderCore.hpp"

namespace Panthera
{

    struct VertexData
    {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    struct Renderer2DStorage
    {
        // Triangle
        static constexpr uint32_t MaxTriangleTriangles = 25037;
        static constexpr uint32_t MaxTriangleVertices = MaxTriangleTriangles * 3;
        static constexpr uint32_t MaxTriangleIndices = MaxTriangleVertices * 3;

        Ref<Shader> TriangleShader = nullptr;
        Ref<VertexArray> TriangleVertexArray = nullptr;
        Ref<VertexBuffer> TriangleVertexBuffer = nullptr;
        Ref<IndexBuffer> TriangleIndexBuffer = nullptr;
        VertexData* TriangleVertices = nullptr;
        uint32_t TriangleIndicesCount = 0;
        uint32_t TriangleVerticesCount = 0;

        // Quad
        static constexpr uint32_t MaxQuadTriangles = 25037;
        static constexpr uint32_t MaxQuadVertices = MaxQuadTriangles * 4;
        static constexpr uint32_t MaxQuadIndices = MaxQuadVertices * 6;

        Ref<Shader> QuadShader = nullptr;
        Ref<VertexArray> QuadVertexArray = nullptr;
        Ref<VertexBuffer> QuadVertexBuffer = nullptr;
        Ref<IndexBuffer> QuadIndexBuffer = nullptr;
        VertexData* QuadVertices = nullptr;
        uint32_t QuadIndicesCount = 0;
        uint32_t QuadVerticesCount = 0;
    };

    void Renderer2D::InitTriangle(Ref <Shader> &shader)
    {
        m_Storage->TriangleShader = shader;

        m_Storage->TriangleVertexArray = VertexArray::Create();
        m_Storage->TriangleVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxTriangleVertices * sizeof(VertexData));
        m_Storage->TriangleVertexBuffer->SetBufferLayout({
                                                                 { ShaderDataType::Float3, "inPosition" },
                                                                 { ShaderDataType::Float4, "inColor" }
                                                         });

        m_Storage->TriangleVertexArray->AddVertexBuffer(m_Storage->TriangleVertexBuffer);

        uint32_t *indices = new uint32_t[Renderer2DStorage::MaxTriangleIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2DStorage::MaxTriangleIndices; i += 3)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            offset += 3;
        }

        m_Storage->TriangleIndexBuffer = IndexBuffer::Create(indices, Renderer2DStorage::MaxTriangleIndices);

        m_Storage->TriangleVertexArray->SetIndexBuffer(m_Storage->TriangleIndexBuffer);
        m_Storage->TriangleVertices = new VertexData[Renderer2DStorage::MaxTriangleVertices];

        delete [] indices;
    }

    void Renderer2D::InitQuad(Ref <Shader> &shader)
    {
        m_Storage->QuadShader = shader;

        m_Storage->QuadVertexArray = VertexArray::Create();
        m_Storage->QuadVertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxQuadVertices * sizeof(VertexData));
        m_Storage->QuadVertexBuffer->SetBufferLayout({
                                                             { ShaderDataType::Float3, "inPosition" },
                                                             { ShaderDataType::Float4, "inColor" }
                                                     });
        m_Storage->QuadVertexArray->AddVertexBuffer(m_Storage->QuadVertexBuffer);

        uint32_t *indices = new uint32_t[Renderer2DStorage::MaxQuadIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2DStorage::MaxQuadIndices; i += 6)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        m_Storage->QuadIndexBuffer = IndexBuffer::Create(indices, Renderer2DStorage::MaxQuadIndices);
        m_Storage->QuadVertexArray->SetIndexBuffer(m_Storage->QuadIndexBuffer);
        m_Storage->QuadVertices = new VertexData[Renderer2DStorage::MaxQuadVertices];

        delete [] indices;
    }

    void Renderer2D::Init()
    {
        m_Storage = new Renderer2DStorage();

        Ref<Shader> defaultShader = nullptr;

        if (ShaderLibrary::Exists("PT_Renderer2D_default"))
        {
            defaultShader = ShaderLibrary::Get("PT_Renderer2D_default");
        }
        else
        {
            defaultShader = ShaderLibrary::Load(AssetLoader::GetAssetPath("Panthera/assets/shader/PT_Renderer2D_default.glsl"));
        }

        InitTriangle(defaultShader);
        InitQuad(defaultShader);
    }

    void Renderer2D::Shutdown()
    {
        delete m_Storage;
    }

    void Renderer2D::DrawIndexed(uint32_t count)
    {
        RenderCommand::DrawIndexed(count);
    }

    void Renderer2D::Flush()
    {
        RenderCommand::EnableBlending();

        if (m_Storage->TriangleVerticesCount > 0)
        {
            m_Storage->TriangleVertexBuffer->SetData(m_Storage->TriangleVertices, m_Storage->TriangleVerticesCount * sizeof(VertexData));
            m_Storage->TriangleVertexArray->Bind();
            m_Storage->TriangleShader->Bind();

            DrawIndexed(m_Storage->TriangleIndicesCount);

            m_Storage->TriangleIndicesCount = 0;
            m_Storage->TriangleVerticesCount = 0;
        }

        if (m_Storage->QuadVerticesCount > 0)
        {
            m_Storage->QuadVertexBuffer->SetData(m_Storage->QuadVertices, m_Storage->QuadVerticesCount * sizeof(VertexData));
            m_Storage->QuadVertexArray->Bind();
            m_Storage->QuadShader->Bind();

            DrawIndexed(m_Storage->QuadIndicesCount);

            m_Storage->QuadIndicesCount = 0;
            m_Storage->QuadVerticesCount = 0;
        }

    }

    void Renderer2D::DrawTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color)
    {
        if (m_Storage->TriangleVerticesCount >= Renderer2DStorage::MaxTriangleVertices)
        {
            Flush();
        }

        for (uint8_t i = 0; i < 3; i++)
        {
            m_Storage->TriangleVertices[m_Storage->TriangleVerticesCount].Position = glm::vec3(i == 0 ? p1 : i == 1 ? p2 : p3, 0.0f);
            m_Storage->TriangleVertices[m_Storage->TriangleVerticesCount].Color = color;
            m_Storage->TriangleVerticesCount++;
        }

        m_Storage->TriangleIndicesCount += 3;
    }

    void Renderer2D::DrawTriangle(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec4 &color)
    {
        if (m_Storage->TriangleVerticesCount >= Renderer2DStorage::MaxTriangleVertices)
        {
            Flush();
        }

        for (uint8_t i = 0; i < 3; i++)
        {
            m_Storage->TriangleVertices[m_Storage->TriangleVerticesCount].Position = i == 0 ? p1 : i == 1 ? p2 : p3;
            m_Storage->TriangleVertices[m_Storage->TriangleVerticesCount].Color = color;
            m_Storage->TriangleVerticesCount++;
        }

        m_Storage->TriangleIndicesCount += 3;
    }

    void Renderer2D::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        if (m_Storage->QuadVerticesCount >= Renderer2DStorage::MaxQuadVertices)
        {
            Flush();
        }

        static const glm::vec4 quadPositions[4] = {
                {-0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f, 0.5f, 0.0f, 1.0f},
                {-0.5f, 0.5f, 0.0f, 1.0f}
        };

        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        for (uint8_t i = 0; i < 4; i++)
        {
            m_Storage->QuadVertices[m_Storage->QuadVerticesCount].Position = transform * quadPositions[i];
            m_Storage->QuadVertices[m_Storage->QuadVerticesCount].Color = color;
            m_Storage->QuadVerticesCount++;
        }

        m_Storage->QuadIndicesCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        if (m_Storage->QuadVerticesCount >= Renderer2DStorage::MaxQuadVertices)
        {
            Flush();
        }

        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), glm::vec3(center, 0.f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        static const glm::vec4 quadPositions[4] = {
                {-0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f, 0.5f, 0.0f, 1.0f},
                {-0.5f, 0.5f, 0.0f, 1.0f}
        };

        for (uint8_t i = 0; i < 4; i++)
        {
            m_Storage->QuadVertices[m_Storage->QuadVerticesCount].Position = transform * quadPositions[i];
            m_Storage->QuadVertices[m_Storage->QuadVerticesCount].Color = color;
            m_Storage->QuadVerticesCount++;
        }

        m_Storage->QuadIndicesCount += 6;
    }
}