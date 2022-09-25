#include "Renderer2D.hpp"

#include "RenderCommands.hpp"
#include "Panthera/RenderCore.hpp"

namespace Panthera
{

    struct Vertex
    {
        glm::vec3 Position;
    };

    struct Renderer2DStorage
    {
        static constexpr uint32_t MaxTriangles = 25037;
        static constexpr uint32_t MaxVertices = MaxTriangles * 3;
        static constexpr uint32_t MaxIndices = MaxVertices;

        Ref<Shader> Shader = nullptr;
        Ref<VertexArray> VertexArray = nullptr;
        Ref<VertexBuffer> VertexBuffer = nullptr;
        Ref<IndexBuffer> IndexBuffer = nullptr;
        Vertex* Vertecies = nullptr;
        uint32_t IndicesCount = 0;
        uint32_t VerticesCount = 0;
    };

    void Renderer2D::Init()
    {
        m_Storage = new Renderer2DStorage();

        if (ShaderLibrary::Exists("FlatColor"))
        {
            m_Storage->Shader = ShaderLibrary::Get("FlatColor");
        }
        else
        {
            m_Storage->Shader = ShaderLibrary::Load(AssetLoader::GetAssetPath("Panthera/assets/shader/FlatColor.glsl"));
        }

        m_Storage->VertexArray = VertexArray::Create();
        m_Storage->VertexBuffer = VertexBuffer::Create(Renderer2DStorage::MaxVertices * sizeof(Vertex));
        m_Storage->VertexBuffer->SetBufferLayout({
            { ShaderDataType::Float3, "a_Position" }
        });

        m_Storage->VertexArray->AddVertexBuffer(m_Storage->VertexBuffer);

        uint32_t *indices = new uint32_t[Renderer2DStorage::MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2DStorage::MaxIndices; i += 3)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            offset += 3;
        }

        m_Storage->IndexBuffer = IndexBuffer::Create(indices, Renderer2DStorage::MaxIndices);
        delete [] indices;

        m_Storage->VertexArray->SetIndexBuffer(m_Storage->IndexBuffer);
        m_Storage->Vertecies = new Vertex[Renderer2DStorage::MaxVertices];

        Ref<UniformBuffer> uniformBuffer = UniformBuffer::Create(sizeof(glm::vec4), 0);
        glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};
        uniformBuffer->SetData(&color, sizeof(glm::vec4), 0);
    }

    void Renderer2D::Shutdown()
    {
        delete m_Storage;
    }

    void Renderer2D::DrawIndexed(uint32_t count)
    {
        m_Storage->VertexArray->Bind();
        RenderCommand::DrawIndexed(count);
    }

    void Renderer2D::DrawTriangle(const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3)
    {
        if (m_Storage->VerticesCount >= Renderer2DStorage::MaxVertices)
        {
            Flush();
        }

        m_Storage->Vertecies[m_Storage->VerticesCount++] = { { p1.x, p1.y, 0.0f } };
        m_Storage->Vertecies[m_Storage->VerticesCount++] = { { p2.x, p2.y, 0.0f } };
        m_Storage->Vertecies[m_Storage->VerticesCount++] = { { p3.x, p3.y, 0.0f } };

        m_Storage->IndicesCount += 3;
    }

    void Renderer2D::Flush()
    {
        m_Storage->VertexBuffer->SetData(m_Storage->Vertecies, m_Storage->VerticesCount * sizeof(Vertex));
        m_Storage->VertexArray->Bind();
        m_Storage->Shader->Bind();

        DrawIndexed(m_Storage->IndicesCount);

        m_Storage->IndicesCount = 0;
        m_Storage->VerticesCount = 0;

    }
}