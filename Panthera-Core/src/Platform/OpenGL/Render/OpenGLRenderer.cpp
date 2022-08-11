#include "OpenGLRenderer.hpp"

#include <glad/glad.h>
#include "Panthera/Render/VertexArray/VertexArray.hpp"
#include "Panthera/Render/Texture/Texture.hpp"
#include "Panthera/Render/Shader/Shader.hpp"
#include "Panthera/Render/Buffer/VertexBuffer.hpp"
#include "Panthera/Render/Buffer/IndexBuffer.hpp"
#include "Panthera/Core/Pointer.hpp"
#include "Panthera/Core/Log.hpp"
#include "Panthera/Core/Application.hpp"
#include <array>

namespace Panthera
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float Index;
        float TilingFactor;
    };

    struct RendererData
    {
        static const uint32_t MAX_QUADS = 25037; // prime
        static const uint32_t MAX_INDICES = MAX_QUADS * 6;
        static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static const uint32_t MAX_TEXTURES = 32;
        Ref <Shader> QuadShader;
        Ref <VertexArray> QuadVertexArray;
        Ref <VertexBuffer> QuadVertexBuffer;
        Ref <IndexBuffer> QuadIndexBuffer;

        std::array<Ref<Texture2D>, RendererData::MAX_TEXTURES> Textures;
        uint32_t TextureIndex = 0;
        QuadVertex *Vertices;
        uint32_t IndicesCount;
        uint32_t VerticesCount;
    };

    static RendererData *s_RendererData = nullptr;

    OpenGLRenderer::OpenGLRenderer()
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    static void InitQuad()
    {
        s_RendererData->Vertices = new QuadVertex[RendererData::MAX_VERTICES];

        uint32_t *indices = new uint32_t[RendererData::MAX_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < RendererData::MAX_INDICES; i += 6)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset += 4;
        }

        s_RendererData->QuadShader = ShaderLibrary::CreateShader("Quad", Application::GetInstance()->GetAssetPath(
                "Panthera/Assets/Shader/Quad.glsl"));

        s_RendererData->QuadVertexArray = VertexArray::Create();
        s_RendererData->QuadVertexBuffer = VertexBuffer::Create(RendererData::MAX_VERTICES * sizeof(QuadVertex));
        s_RendererData->QuadVertexBuffer->SetBufferLayout({
                                                              {"a_Position", ShaderDataType::Float3},
                                                              {"a_Color",    ShaderDataType::Float4},
                                                              {"a_TexCoord", ShaderDataType::Float2},
                                                              {"a_Index",    ShaderDataType::Float},
                                                              {"a_Tiling",   ShaderDataType::Float}
                                                      });

        s_RendererData->QuadIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_INDICES);
        s_RendererData->QuadVertexArray->AddVertexBuffer(s_RendererData->QuadVertexBuffer);
        s_RendererData->QuadVertexArray->SetIndexBuffer(s_RendererData->QuadIndexBuffer);
        delete[] indices;
    }

    static void InitTriangle()
    {

    }

    void OpenGLRenderer::Init()
    {
        s_RendererData = new RendererData;
        s_RendererData->Textures[0] = Texture2D::Create(1, 1);
        uint32_t textureData = 0xFFFFFFFF;
        s_RendererData->Textures[0]->SetData(&textureData, sizeof(uint32_t));

        InitQuad();
        InitTriangle();
    }

    void OpenGLRenderer::Flush()
    {
        if (s_RendererData->VerticesCount == 0)
        {
            return;
        }

        s_RendererData->QuadVertexBuffer->AddData(s_RendererData->Vertices, s_RendererData->VerticesCount * sizeof(QuadVertex));

        for (uint32_t i = 0; i < s_RendererData->TextureIndex; i++)
        {
            s_RendererData->Textures[i]->Bind(i);
        }

        s_RendererData->QuadShader->Bind();
        s_RendererData->QuadVertexArray->Bind();
        DrawIndexed(s_RendererData->IndicesCount);

        s_RendererData->IndicesCount = 0;
        s_RendererData->VerticesCount = 0;
        s_RendererData->TextureIndex = 1;
    }

    void OpenGLRenderer::BeginScene()
    {
        s_RendererData->IndicesCount = 0;
        s_RendererData->VerticesCount = 0;
        s_RendererData->TextureIndex = 1;
    }

    void OpenGLRenderer::EndScene()
    {
        Flush();
    }

    void OpenGLRenderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawIndexed(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        if (s_RendererData->IndicesCount + 6 > RendererData::MAX_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};
        for (uint32_t i = 0; i < 4; i++)
        {
            s_RendererData->Vertices[s_RendererData->VerticesCount].Position
                    = center + glm::vec3(size.x * ((i == 0 || i == 3) ? -1.f : 1.f) / 2,
                                         size.y * ((i >= 2) ? 1.f : -1.f) / 2, 0.f);
            s_RendererData->Vertices[s_RendererData->VerticesCount].Color = color;
            s_RendererData->Vertices[s_RendererData->VerticesCount].TexCoord = texCoords[i];
            s_RendererData->Vertices[s_RendererData->VerticesCount].Index = 0;
            s_RendererData->Vertices[s_RendererData->VerticesCount].TilingFactor = 1.f;
            s_RendererData->VerticesCount++;
        }

        s_RendererData->IndicesCount += 6;
    }

    void OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color);
    }

    void OpenGLRenderer::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color,
                                  float Tiling,
                                  Ref <Texture2D> &texture)
    {
        ASSERT(texture, "Texture is nullptr");
        if (s_RendererData->IndicesCount + 6 > RendererData::MAX_INDICES)
        {
            Flush();
        }
        if (s_RendererData->TextureIndex == RendererData::MAX_TEXTURES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {
                {0, 0},
                {1, 0},
                {1, 1},
                {0, 1}
        };
        for (uint32_t i = 0; i < 4; i++)
        {
            s_RendererData->Vertices[s_RendererData->VerticesCount].Position
                    = center + glm::vec3(size.x * ((i == 0 || i == 3) ? -1.f : 1.f) / 2,
                                         size.y * ((i >= 2) ? 1.f : -1.f) / 2, 0.f);
            s_RendererData->Vertices[s_RendererData->VerticesCount].Color = color;
            s_RendererData->Vertices[s_RendererData->VerticesCount].TexCoord = texCoords[i];
            s_RendererData->Vertices[s_RendererData->VerticesCount].Index = s_RendererData->TextureIndex;
            s_RendererData->Vertices[s_RendererData->VerticesCount].TilingFactor = Tiling;
            s_RendererData->VerticesCount++;
        }

        s_RendererData->IndicesCount += 6;
        s_RendererData->Textures[s_RendererData->TextureIndex] = texture;
        s_RendererData->TextureIndex++;
    }

    void OpenGLRenderer::DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color)
    {

    }

    void OpenGLRenderer::DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color)
    {

    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling,
                                 Ref <Texture2D> &texture)
    {

    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling,
                                 Ref <Texture2D> &texture)
    {

    }

    void OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color,
                                  float tiling,
                                  Ref <Texture2D> &texture)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color, tiling, texture);
    }
}