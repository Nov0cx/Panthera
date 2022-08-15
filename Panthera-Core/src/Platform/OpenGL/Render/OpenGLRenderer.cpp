#include "OpenGLRenderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Panthera/Render/VertexArray/VertexArray.hpp"
#include "Panthera/Render/Texture/Texture.hpp"
#include "Panthera/Render/Shader/Shader.hpp"
#include "Panthera/Render/Shader/UniformBuffer.hpp"
#include "Panthera/Render/Camera/OrthographicCamera.hpp"
#include "Panthera/Render/Buffer/VertexBuffer.hpp"
#include "Panthera/Render/Buffer/IndexBuffer.hpp"
#include "Panthera/Render/Framebuffer/Framebuffer.hpp"
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

    struct TriangleVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float Index;
        float TilingFactor;
    };

    struct CircleVertex
    {
        glm::vec3 Position;
        glm::vec3 InterpolatingPosition;
        glm::vec4 Color;
        float Fade;
        float Border;
        glm::vec2 TexCoord;
        float Index;
        float TilingFactor;
    };

    struct LineVertex
    {
        glm::vec3 Position;
        glm::vec3 PosA;
        glm::vec3 PosB;
        glm::vec2 InterpolatingPosition;
        float Thickness;
        glm::vec4 Color;
    };

    struct RendererData
    {
        static const uint32_t MAX_TEXTURES = 32;

        static const uint32_t MAX_QUADS = 25037; // prime
        static const uint32_t MAX_QUAD_INDICES = MAX_QUADS * 6;
        static const uint32_t MAX_QUAD_VERTICES = MAX_QUADS * 4;

        static const uint32_t MAX_TRIANGLES = 25037; // prime
        static const uint32_t MAX_TRIANGLE_INDICES = MAX_TRIANGLES * 3;
        static const uint32_t MAX_TRIANGLE_VERTICES = MAX_TRIANGLES * 3;

        static const uint32_t MAX_CIRCLES = 25037; // prime
        static const uint32_t MAX_CIRCLE_INDICES = MAX_CIRCLES * 6;
        static const uint32_t MAX_CIRCLE_VERTICES = MAX_CIRCLES * 4;

        static const uint32_t MAX_LINES = 25037; // prime
        static const uint32_t MAX_LINE_INDICES = MAX_LINES * 6;
        static const uint32_t MAX_LINE_VERTICES = MAX_LINES * 4;

        std::array <Ref<Texture2D>, RendererData::MAX_TEXTURES> Textures;
        uint32_t TextureIndex = 0;

        Ref <UniformBuffer> CameraUniformBuffer;

        Ref <Shader> QuadShader;
        Ref <VertexArray> QuadVertexArray;
        Ref <VertexBuffer> QuadVertexBuffer;
        Ref <IndexBuffer> QuadIndexBuffer;
        QuadVertex *QuadVertices;
        uint32_t QuadIndicesCount;
        uint32_t QuadVerticesCount;
        std::array<glm::vec4, 4> QuadPositions;

        Ref <Shader> TriangleShader;
        Ref <VertexArray> TriangleVertexArray;
        Ref <VertexBuffer> TriangleVertexBuffer;
        Ref <IndexBuffer> TriangleIndexBuffer;
        TriangleVertex *TriangleVertices;
        uint32_t TriangleIndicesCount;
        uint32_t TriangleVerticesCount;
        std::array<glm::vec4, 3> TrianglePositions;

        Ref <Shader> CircleShader;
        Ref <VertexArray> CircleVertexArray;
        Ref <VertexBuffer> CircleVertexBuffer;
        Ref <IndexBuffer> CircleIndexBuffer;
        CircleVertex *CircleVertices;
        uint32_t CircleIndicesCount;
        uint32_t CircleVerticesCount;
        std::array<glm::vec4, 4> CirclePositions;

        Ref <Shader> LineShader;
        Ref <VertexArray> LineVertexArray;
        Ref <VertexBuffer> LineVertexBuffer;
        Ref <IndexBuffer> LineIndexBuffer;
        LineVertex *LineVertices;
        uint32_t LineIndicesCount;
        uint32_t LineVerticesCount;
        std::array<glm::vec4, 4> LinePositions;

        Ref <Framebuffer> Framebuffer;
    };

    static RendererData *s_RendererData = nullptr;

    static void InitQuad()
    {
        s_RendererData->QuadVertices = new QuadVertex[RendererData::MAX_QUAD_VERTICES];

        uint32_t *indices = new uint32_t[RendererData::MAX_QUAD_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < RendererData::MAX_QUAD_INDICES; i += 6)
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
        s_RendererData->QuadVertexBuffer = VertexBuffer::Create(RendererData::MAX_QUAD_VERTICES * sizeof(QuadVertex));
        s_RendererData->QuadVertexBuffer->SetBufferLayout({
                                                                  {"a_Position", ShaderDataType::Float3},
                                                                  {"a_Color",    ShaderDataType::Float4},
                                                                  {"a_TexCoord", ShaderDataType::Float2},
                                                                  {"a_Index",    ShaderDataType::Float},
                                                                  {"a_Tiling",   ShaderDataType::Float}
                                                          });

        s_RendererData->QuadIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_QUAD_INDICES);
        s_RendererData->QuadVertexArray->AddVertexBuffer(s_RendererData->QuadVertexBuffer);
        s_RendererData->QuadVertexArray->SetIndexBuffer(s_RendererData->QuadIndexBuffer);
        delete[] indices;

        s_RendererData->QuadPositions = {{
                                                 {-0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, 0.5f, 0.0f, 1.f},
                                                 {-0.5f, 0.5f, 0.0f, 1.f}
                                         }};
    }

    static void InitTriangle()
    {
        s_RendererData->TriangleVertices = new TriangleVertex[RendererData::MAX_TRIANGLE_VERTICES];
        uint32_t *indices = new uint32_t[RendererData::MAX_TRIANGLE_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < RendererData::MAX_TRIANGLE_INDICES; i += 3)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            offset += 3;
        }
        s_RendererData->TriangleShader = ShaderLibrary::CreateShader("Triangle",
                                                                     Application::GetInstance()->GetAssetPath(
                                                                             "Panthera/Assets/Shader/Triangle.glsl"));
        s_RendererData->TriangleVertexArray = VertexArray::Create();
        s_RendererData->TriangleVertexBuffer = VertexBuffer::Create(
                RendererData::MAX_TRIANGLE_VERTICES * sizeof(TriangleVertex));
        s_RendererData->TriangleVertexBuffer->SetBufferLayout({
                                                                      {"a_Position", ShaderDataType::Float3},
                                                                      {"a_Color",    ShaderDataType::Float4},
                                                                      {"a_TexCoord", ShaderDataType::Float2},
                                                                      {"a_Index",    ShaderDataType::Float},
                                                                      {"a_Tiling",   ShaderDataType::Float}
                                                              });
        s_RendererData->TriangleIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_TRIANGLE_INDICES);
        s_RendererData->TriangleVertexArray->AddVertexBuffer(s_RendererData->TriangleVertexBuffer);
        s_RendererData->TriangleVertexArray->SetIndexBuffer(s_RendererData->TriangleIndexBuffer);
        delete[] indices;

        s_RendererData->TrianglePositions = {{
                                                     {-0.5f, -0.5f, 0.0f, 1.f},
                                                     {0.5f, -0.5f, 0.0f, 1.f},
                                                     {0.0f, 0.5f, 0.0f, 1.f}
                                             }};
    }

    static void InitCircle()
    {
        s_RendererData->CircleVertices = new CircleVertex[RendererData::MAX_CIRCLE_VERTICES];

        uint32_t *indices = new uint32_t[RendererData::MAX_CIRCLE_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < RendererData::MAX_CIRCLE_INDICES; i += 6)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset += 4;
        }

        s_RendererData->CircleShader = ShaderLibrary::CreateShader("FilledCircle",
                                                                   Application::GetInstance()->GetAssetPath(
                                                                           "Panthera/Assets/Shader/FilledCircle.glsl"));

        s_RendererData->CircleVertexArray = VertexArray::Create();
        s_RendererData->CircleVertexBuffer = VertexBuffer::Create(
                RendererData::MAX_CIRCLE_VERTICES * sizeof(CircleVertex));
        s_RendererData->CircleVertexBuffer->SetBufferLayout({
                                                                    {"a_Position", ShaderDataType::Float3},
                                                                    {"a_Center",   ShaderDataType::Float3},
                                                                    {"a_Color",    ShaderDataType::Float4},
                                                                    {"a_Radius",   ShaderDataType::Float},
                                                                    {"a_Border",   ShaderDataType::Float},
                                                                    {"a_TexCoord", ShaderDataType::Float2},
                                                                    {"a_Index",    ShaderDataType::Float},
                                                                    {"a_Tiling",   ShaderDataType::Float}
                                                            });

        s_RendererData->CircleIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_CIRCLE_INDICES);
        s_RendererData->CircleVertexArray->AddVertexBuffer(s_RendererData->CircleVertexBuffer);
        s_RendererData->CircleVertexArray->SetIndexBuffer(s_RendererData->CircleIndexBuffer);
        delete[] indices;

        s_RendererData->CirclePositions = {{
                                                   {-0.5f, -0.5f, 0.0f, 1.f},
                                                   {0.5f, -0.5f, 0.0f, 1.f},
                                                   {0.5f, 0.5f, 0.0f, 1.f},
                                                   {-0.5f, 0.5f, 0.0f, 1.f}
                                           }};
    }

    static void InitLine()
    {
        s_RendererData->LineVertices = new LineVertex[RendererData::MAX_LINE_VERTICES];

        uint32_t *indices = new uint32_t[RendererData::MAX_LINE_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < RendererData::MAX_LINE_INDICES; i += 6)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset += 4;
        }

        s_RendererData->LineShader = ShaderLibrary::CreateShader("Line",
                                                                 Application::GetInstance()->GetAssetPath(
                                                                         "Panthera/Assets/Shader/Line.glsl"));

        s_RendererData->LineVertexArray = VertexArray::Create();
        s_RendererData->LineVertexBuffer = VertexBuffer::Create(
                RendererData::MAX_LINE_VERTICES * sizeof(LineVertex));
        s_RendererData->LineVertexBuffer->SetBufferLayout({
                                                                  {"a_Position",              ShaderDataType::Float3},
                                                                  {"a_PosA",                  ShaderDataType::Float3},
                                                                  {"a_PosB",                  ShaderDataType::Float3},
                                                                  {"a_InterpolatingPosition", ShaderDataType::Float2},
                                                                  {"a_Thickness",             ShaderDataType::Float},
                                                                  {"a_Color",                 ShaderDataType::Float4},
                                                          });

        s_RendererData->LineIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_LINE_INDICES);
        s_RendererData->LineVertexArray->AddVertexBuffer(s_RendererData->LineVertexBuffer);
        s_RendererData->LineVertexArray->SetIndexBuffer(s_RendererData->LineIndexBuffer);
        delete[] indices;

        s_RendererData->LinePositions = {{
                                                 {-0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, 0.5f, 0.0f, 1.f},
                                                 {-0.5f, 0.5f, 0.0f, 1.f}
                                         }};
    }

    void OpenGLRenderer::Init()
    {
        s_RendererData = new RendererData;
        s_RendererData->Textures[0] = Texture2D::Create(Texture2DSpecification{});
        uint32_t textureData = 0xFFFFFFFF;
        s_RendererData->Textures[0]->SetData(&textureData, sizeof(uint32_t));

        s_RendererData->CameraUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);

        InitQuad();
        InitTriangle();
        InitCircle();
        InitLine();

        s_RendererData->Framebuffer = Framebuffer::Create({
            FramebufferAttachmentSpecification {
                .AttachmentType = FramebufferAttachmentType::Color,
                .TextureSpecification = Texture2DSpecification {
                    .Width = Application::GetInstance()->GetWindowWidth(),
                    .Height = Application::GetInstance()->GetWindowHeight(),
                    .InternalFormat = Texture2DInternalFormat::RGBA8,
                    .DataFormat = Texture2DDataFormat::RGBA,
                    .Filter = Texture2DFilter::Linear,
                    .Wrapping = Texture2DWrapping::ClampToEdge,
                }
            },
            FramebufferAttachmentSpecification {
                .AttachmentType = FramebufferAttachmentType::Depth,
                .TextureSpecification = Texture2DSpecification {
                    .Width = Application::GetInstance()->GetWindowWidth(),
                    .Height = Application::GetInstance()->GetWindowHeight(),
                    .InternalFormat = Texture2DInternalFormat::Depth24Stencil8,
                    .DataFormat = Texture2DDataFormat::DepthStencil,
                    .Filter = Texture2DFilter::Linear,
                    .Wrapping = Texture2DWrapping::ClampToEdge,
                }
            }
        });
        s_RendererData->Framebuffer->Unbind();
    }

    void OpenGLRenderer::Flush()
    {
        ASSERT(s_RendererData, "Renderer not initialized!");
        for (uint32_t i = 0; i < s_RendererData->TextureIndex; i++)
        {
            s_RendererData->Textures[i]->Bind(i);
        }

        if (s_RendererData->QuadVerticesCount)
        {
            s_RendererData->QuadVertexBuffer->AddData(s_RendererData->QuadVertices,
                                                      s_RendererData->QuadVerticesCount * sizeof(QuadVertex));


            s_RendererData->QuadShader->Bind();
            s_RendererData->QuadVertexArray->Bind();
            DrawIndexed(s_RendererData->QuadIndicesCount);

            s_RendererData->QuadIndicesCount = 0;
            s_RendererData->QuadVerticesCount = 0;
        }

        if (s_RendererData->TriangleVerticesCount)
        {
            s_RendererData->TriangleVertexBuffer->AddData(s_RendererData->TriangleVertices,
                                                          s_RendererData->TriangleVerticesCount *
                                                          sizeof(TriangleVertex));

            s_RendererData->TriangleShader->Bind();
            s_RendererData->TriangleVertexArray->Bind();
            DrawIndexed(s_RendererData->TriangleIndicesCount);

            s_RendererData->TriangleIndicesCount = 0;
            s_RendererData->TriangleVerticesCount = 0;
        }

        if (s_RendererData->CircleVerticesCount)
        {
            s_RendererData->CircleVertexBuffer->AddData(s_RendererData->CircleVertices,
                                                        s_RendererData->CircleVerticesCount * sizeof(CircleVertex));
            s_RendererData->CircleShader->Bind();
            s_RendererData->CircleVertexArray->Bind();
            DrawIndexed(s_RendererData->CircleIndicesCount);
            s_RendererData->CircleIndicesCount = 0;
            s_RendererData->CircleVerticesCount = 0;
        }

        if (s_RendererData->LineVerticesCount)
        {
            s_RendererData->LineVertexBuffer->AddData(s_RendererData->LineVertices,
                                                      s_RendererData->LineVerticesCount * sizeof(LineVertex));
            s_RendererData->LineShader->Bind();
            s_RendererData->LineVertexArray->Bind();
            DrawIndexed(s_RendererData->LineIndicesCount);
            s_RendererData->LineIndicesCount = 0;
            s_RendererData->LineVerticesCount = 0;
        }

        s_RendererData->TextureIndex = 1;
    }

    void OpenGLRenderer::BeginScene()
    {
        s_RendererData->QuadIndicesCount = 0;
        s_RendererData->QuadVerticesCount = 0;
        s_RendererData->TextureIndex = 1;

        glm::mat4 identity = glm::mat4(1.0f);
        s_RendererData->CameraUniformBuffer->SetData(&identity, sizeof(glm::mat4));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderer::BeginScene(OrthographicCamera &camera)
    {
        s_RendererData->QuadIndicesCount = 0;
        s_RendererData->QuadVerticesCount = 0;
        s_RendererData->TextureIndex = 1;

        s_RendererData->CameraUniformBuffer->SetData(&camera.GetViewProjectionMatrix(), sizeof(glm::mat4));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderer::EndScene()
    {
        Flush();
    }

    void OpenGLRenderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawIndexed(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

#pragma section("Quad")

    void OpenGLRenderer::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawQuad(transform, color);
    }

    void OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color);
    }

    void OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color,
                                  float tiling,
                                  Ref <Texture2D> &texture)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color, tiling, texture);
    }

    void OpenGLRenderer::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color,
                                  float tiling,
                                  Ref <Texture2D> &texture)
    {
        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawQuad(transform, color, tiling, texture);
    }

    void
    OpenGLRenderer::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), center)
                              * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
                              * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawQuad(transform, color);
    }

    void
    OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, rotation, color);
    }

    void
    OpenGLRenderer::DrawQuad(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color,
                             float tiling, Ref <Texture2D> &texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), center)
                              * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
                              * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawQuad(transform, color, tiling, texture);
    }

    void
    OpenGLRenderer::DrawQuad(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color,
                             float tiling, Ref <Texture2D> &texture)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, rotation, color, tiling, texture);
    }

    void OpenGLRenderer::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
    {
        ASSERT(s_RendererData, "Renderer data is null");
        if (s_RendererData->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};
        for (uint32_t i = 0; i < 4; i++)
        {
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].Position
                    = transform * s_RendererData->QuadPositions[i];
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].Color = color;
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].TexCoord = texCoords[i];
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].Index = 0;
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].TilingFactor = 1.f;
            s_RendererData->QuadVerticesCount++;
        }

        s_RendererData->QuadIndicesCount += 6;
    }

    void
    OpenGLRenderer::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref <Texture2D> &texture)
    {
        ASSERT(texture, "Texture is nullptr");
        ASSERT(s_RendererData, "Renderer data is null");
        if (s_RendererData->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        bool found = false;
        float index = 0;

        for (uint8_t i = 0; i < s_RendererData->TextureIndex; i++)
        {
            if (s_RendererData->Textures[i] == texture)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (s_RendererData->TextureIndex == RendererData::MAX_TEXTURES && !found)
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
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].Position
                    = transform * s_RendererData->QuadPositions[i];
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].Color = color;
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].TexCoord = texCoords[i];
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].Index = found ? index
                                                                                          : s_RendererData->TextureIndex;
            s_RendererData->QuadVertices[s_RendererData->QuadVerticesCount].TilingFactor = tiling;
            s_RendererData->QuadVerticesCount++;
        }

        s_RendererData->QuadIndicesCount += 6;
        if (!found)
        {
            s_RendererData->Textures[s_RendererData->TextureIndex] = texture;
            s_RendererData->TextureIndex++;
        }
    }

#pragma section("Triangle")

    void OpenGLRenderer::DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawTriangle(transform, color);
    }

    void OpenGLRenderer::DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawTriangle(glm::vec3(center.x, center.y, 0.f), size, color);
    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling,
                                 Ref <Texture2D> &texture)
    {
        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawTriangle(transform, color, tiling, texture);
    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, const glm::vec4 &color, float tiling,
                                 Ref <Texture2D> &texture)
    {
        DrawTriangle(glm::vec3(center.x, center.y, 0.f), size, color, tiling, texture);
    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), center)
                              * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
                              * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawTriangle(transform, color);
    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        DrawTriangle(glm::vec3(center.x, center.y, 0.f), size, rotation, color);
    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec3 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color,
                                 float tiling, Ref <Texture2D> &texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), center)
                              * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
                              * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));
        DrawTriangle(transform, color, tiling, texture);
    }

    void
    OpenGLRenderer::DrawTriangle(const glm::vec2 &center, const glm::vec2 &size, float rotation, const glm::vec4 &color,
                                 float tiling, Ref <Texture2D> &texture)
    {
        DrawTriangle(glm::vec3(center.x, center.y, 0.f), size, rotation, color, tiling, texture);
    }

    void OpenGLRenderer::DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color)
    {
        ASSERT(s_RendererData, "Renderer data is null");
        if (s_RendererData->TriangleVerticesCount + 3 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1}
        };

        for (uint32_t i = 0; i < 3; i++)
        {
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].Position
                    = transform * s_RendererData->TrianglePositions[i];
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].Color = color;
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].TexCoord = texCoords[i];
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].Index = 0;
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].TilingFactor = 1.f;
            s_RendererData->TriangleVerticesCount++;
        }

        s_RendererData->TriangleIndicesCount += 3;
    }

    void OpenGLRenderer::DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color, float tiling,
                                      Ref <Texture2D> &texture)
    {

        if (s_RendererData->TriangleVerticesCount + 3 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1}
        };

        bool found = false;
        float index = 0;

        for (uint8_t i = 0; i < s_RendererData->TextureIndex; i++)
        {
            if (s_RendererData->Textures[i] == texture)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (s_RendererData->TextureIndex == RendererData::MAX_TEXTURES && !found)
        {
            Flush();
        }

        for (uint32_t i = 0; i < 3; i++)
        {
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].Position
                    = transform * s_RendererData->TrianglePositions[i];
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].Color = color;
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].TexCoord = texCoords[i];
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].Index = found ? index
                                                                                                  : s_RendererData->TextureIndex;
            s_RendererData->TriangleVertices[s_RendererData->TriangleVerticesCount].TilingFactor = 1.f;
            s_RendererData->TriangleVerticesCount++;
        }

        s_RendererData->TriangleIndicesCount += 3;

        if (!found)
        {
            s_RendererData->Textures[s_RendererData->TextureIndex] = texture;
            s_RendererData->TextureIndex++;
        }
    }

#pragma section("Circle")

    void
    OpenGLRenderer::DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness,
                               float fade)
    {
        ASSERT(radius > 0.f, "Radius must be greater than 0")
        ASSERT(borderThickness >= 0.f, "Border thickness must be greater than or equal to 0")
        ASSERT(s_RendererData, "Renderer data is null")
        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) *
                glm::scale(glm::mat4(1.0f), glm::vec3(radius * 2, radius * 2, 1.0f));

        DrawCircle(transform, color, borderThickness, fade);
    }

    void
    OpenGLRenderer::DrawCircle(const glm::vec2 &center, const glm::vec4 &color, float radius, float borderThickness,
                               float fade)
    {
        DrawCircle(glm::vec3(center, 0.f), color, radius, borderThickness, fade);
    }

    void
    OpenGLRenderer::DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness,
                               float fade,
                               float tiling, Ref <Texture2D> &texture)
    {
        ASSERT(texture, "Texture is null")
        ASSERT(radius > 0.f, "Radius must be greater than 0")
        ASSERT(borderThickness >= 0.f, "Border thickness must be greater than or equal to 0")
        ASSERT(s_RendererData, "Renderer data is null")
        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), center) *
                glm::scale(glm::mat4(1.0f), glm::vec3(radius * 2, radius * 2, 1.0f));
        DrawCircle(transform, color, borderThickness, fade, tiling, texture);
        //LOG_INFO("Drawing circle at {0} with radius {1}", center.x, radius);
    }

    void
    OpenGLRenderer::DrawCircle(const glm::vec2 &center, const glm::vec4 &color, float radius, float borderThickness,
                               float fade,
                               float tiling, Ref <Texture2D> &texture)
    {
        DrawCircle(glm::vec3(center, 0.f), color, radius, borderThickness, fade, tiling, texture);
    }

    void
    OpenGLRenderer::DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness,
                               float fade)
    {
        if (s_RendererData->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};
        for (uint32_t i = 0; i < 4; i++)
        {
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Position
                    = transform * s_RendererData->CirclePositions[i];
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].InterpolatingPosition =
                    s_RendererData->CirclePositions[i] * 2.0f; // position between 0 and 1
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Color = color;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Fade = fade;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Border = borderThickness;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].TexCoord = texCoords[i];
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Index = 0;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].TilingFactor = 1.f;
            s_RendererData->CircleVerticesCount++;
        }

        s_RendererData->CircleIndicesCount += 6;
    }

    void
    OpenGLRenderer::DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness,
                               float fade, float tiling, Ref <Texture2D> &texture)
    {
        if (s_RendererData->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};

        bool found = false;
        float index = 0;

        for (uint8_t i = 0; i < s_RendererData->TextureIndex; i++)
        {
            if (s_RendererData->Textures[i] == texture)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (s_RendererData->TextureIndex == RendererData::MAX_TEXTURES && !found)
        {
            Flush();
        }

        for (uint32_t i = 0; i < 4; i++)
        {
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Position
                    = transform * s_RendererData->CirclePositions[i];
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].InterpolatingPosition =
                    s_RendererData->CirclePositions[i] * 2.0f; // position between 0 and 1
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Color = color;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Fade = fade;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Border = borderThickness;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].TexCoord = texCoords[i];
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].Index = found ? index
                                                                                              : s_RendererData->TextureIndex;
            s_RendererData->CircleVertices[s_RendererData->CircleVerticesCount].TilingFactor = tiling;
            s_RendererData->CircleVerticesCount++;
        }

        s_RendererData->CircleIndicesCount += 6;
        if (!found)
        {
            s_RendererData->Textures[s_RendererData->TextureIndex] = texture;
            s_RendererData->TextureIndex++;
        }
    }

#pragma section("Line")

    void OpenGLRenderer::DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color, float thickness)
    {
        if (thickness < 0.0067f)
            thickness = 0.0067f;

        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), (end - start) * 0.5f);

        for (uint32_t i = 0; i < 4; i++)
        {
            s_RendererData->LineVertices[s_RendererData->LineVerticesCount].Position =
                    transform * s_RendererData->LinePositions[i];
            s_RendererData->LineVertices[s_RendererData->LineVerticesCount].InterpolatingPosition =
                    s_RendererData->LinePositions[i] * 2.0f;
            s_RendererData->LineVertices[s_RendererData->LineVerticesCount].PosA = start;
            s_RendererData->LineVertices[s_RendererData->LineVerticesCount].PosB = end;
            s_RendererData->LineVertices[s_RendererData->LineVerticesCount].Thickness = thickness;
            s_RendererData->LineVertices[s_RendererData->LineVerticesCount].Color = color;
            s_RendererData->LineVerticesCount++;
        }
//
        s_RendererData->LineIndicesCount += 6;
    }

}