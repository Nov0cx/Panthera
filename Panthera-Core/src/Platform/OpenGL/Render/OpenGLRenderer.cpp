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

    struct QuadData
    {
        static const uint32_t MAX_QUADS = 25037; // prime
        static const uint32_t MAX_INDICES = MAX_QUADS * 6;
        static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static const uint32_t MAX_TEXTURES = 32;
        Ref <Shader> QuadShader;
        Ref <VertexArray> QuadVertexArray;
        Ref <VertexBuffer> QuadVertexBuffer;
        Ref <IndexBuffer> QuadIndexBuffer;

        std::array<Ref<Texture2D>, QuadData::MAX_TEXTURES> Textures;
        uint32_t TextureIndex = 0;
        QuadVertex *Vertices;
        uint32_t IndicesCount;
        uint32_t VerticesCount;
    };

    static QuadData *s_QuadData = nullptr;

    OpenGLRenderer::OpenGLRenderer()
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    void OpenGLRenderer::Init()
    {
        s_QuadData = new QuadData;
        s_QuadData->Textures[0] = Texture2D::Create(1, 1);
        uint32_t textureData = 0xFFFFFFFF;
        s_QuadData->Textures[0]->SetData(&textureData, sizeof(uint32_t));

        s_QuadData->Vertices = new QuadVertex[QuadData::MAX_VERTICES];

        uint32_t *indices = new uint32_t[QuadData::MAX_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < QuadData::MAX_INDICES; i += 6)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset += 4;
        }

        s_QuadData->QuadShader = ShaderLibrary::CreateShader("Texture", Application::GetInstance()->GetAssetPath(
                "Panthera/Assets/Shader/Texture.glsl"));

        s_QuadData->QuadVertexArray = VertexArray::Create();
        s_QuadData->QuadVertexBuffer = VertexBuffer::Create(QuadData::MAX_VERTICES * sizeof(QuadVertex));
        s_QuadData->QuadVertexBuffer->SetBufferLayout({
                                                              {"a_Position", ShaderDataType::Float3},
                                                              {"a_Color",    ShaderDataType::Float4},
                                                              {"a_TexCoord", ShaderDataType::Float2},
                                                              {"a_Index",    ShaderDataType::Float},
                                                              {"a_Tiling",   ShaderDataType::Float}
                                                      });

        s_QuadData->QuadIndexBuffer = IndexBuffer::Create(indices, QuadData::MAX_INDICES);
        s_QuadData->QuadVertexArray->AddVertexBuffer(s_QuadData->QuadVertexBuffer);
        LOG_INFO("QuadVertexBuffer: {0}", (int)&s_QuadData->QuadVertexBuffer);
        s_QuadData->QuadVertexArray->SetIndexBuffer(s_QuadData->QuadIndexBuffer);
        delete[] indices;
    }

    void OpenGLRenderer::Flush()
    {
        if (s_QuadData->VerticesCount == 0)
        {
            return;
        }

        s_QuadData->QuadVertexBuffer->AddData(s_QuadData->Vertices, s_QuadData->VerticesCount * sizeof(QuadVertex));

        for (uint32_t i = 0; i < s_QuadData->TextureIndex; i++)
        {
            s_QuadData->Textures[i]->Bind(i);
        }

        s_QuadData->QuadShader->Bind();
        s_QuadData->QuadVertexArray->Bind();
        DrawIndexed(s_QuadData->IndicesCount);

        s_QuadData->IndicesCount = 0;
        s_QuadData->VerticesCount = 0;
        s_QuadData->TextureIndex = 1;
    }

    void OpenGLRenderer::BeginScene()
    {
        s_QuadData->IndicesCount = 0;
        s_QuadData->VerticesCount = 0;
        s_QuadData->TextureIndex = 1;
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
        if (s_QuadData->IndicesCount + 6 > QuadData::MAX_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};
        for (uint32_t i = 0; i < 4; i++)
        {
            s_QuadData->Vertices[s_QuadData->VerticesCount].Position
                    = center + glm::vec3(size.x * ((i == 0 || i == 3) ? -1.f : 1.f) / 2,
                                         size.y * ((i >= 2) ? 1.f : -1.f) / 2, 0.f);
            s_QuadData->Vertices[s_QuadData->VerticesCount].Color = color;
            s_QuadData->Vertices[s_QuadData->VerticesCount].TexCoord = texCoords[i];
            s_QuadData->Vertices[s_QuadData->VerticesCount].Index = 0;
            s_QuadData->Vertices[s_QuadData->VerticesCount].TilingFactor = 1.f;
            s_QuadData->VerticesCount++;
        }

        s_QuadData->IndicesCount += 6;
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
        if (s_QuadData->IndicesCount + 6 > QuadData::MAX_INDICES)
        {
            Flush();
        }
        if (s_QuadData->TextureIndex == QuadData::MAX_TEXTURES)
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
            s_QuadData->Vertices[s_QuadData->VerticesCount].Position
                    = center + glm::vec3(size.x * ((i == 0 || i == 3) ? -1.f : 1.f) / 2,
                                         size.y * ((i >= 2) ? 1.f : -1.f) / 2, 0.f);
            s_QuadData->Vertices[s_QuadData->VerticesCount].Color = color;
            s_QuadData->Vertices[s_QuadData->VerticesCount].TexCoord = texCoords[i];
            s_QuadData->Vertices[s_QuadData->VerticesCount].Index = s_QuadData->TextureIndex;
            s_QuadData->Vertices[s_QuadData->VerticesCount].TilingFactor = Tiling;
            s_QuadData->VerticesCount++;
        }

        s_QuadData->IndicesCount += 6;
        s_QuadData->Textures[s_QuadData->TextureIndex] = texture;
        s_QuadData->TextureIndex++;
    }

    void OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color,
                                  float tiling,
                                  Ref <Texture2D> &texture)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color, tiling, texture);
    }
}