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

    static Ref <UniformBuffer> s_CameraUniformBuffer;

    void OpenGLRenderer::InitQuad()
    {
        m_Data->QuadVertices = new QuadVertex[RendererData::MAX_QUAD_VERTICES];

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

        m_Data->QuadShader = ShaderLibrary::CreateShader("Quad", Application::GetInstance()->GetAssetPath(
                "Panthera/Assets/Shader/Quad.glsl"));

        m_Data->QuadVertexArray = VertexArray::Create();
        m_Data->QuadVertexBuffer = VertexBuffer::Create(RendererData::MAX_QUAD_VERTICES * sizeof(QuadVertex));
        m_Data->QuadVertexBuffer->SetBufferLayout({
                                                                  {"a_Position", ShaderDataType::Float3},
                                                                  {"a_Color",    ShaderDataType::Float4},
                                                                  {"a_TexCoord", ShaderDataType::Float2},
                                                                  {"a_Index",    ShaderDataType::Float},
                                                                  {"a_Tiling",   ShaderDataType::Float}
                                                          });

        m_Data->QuadIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_QUAD_INDICES);
        m_Data->QuadVertexArray->AddVertexBuffer(m_Data->QuadVertexBuffer);
        m_Data->QuadVertexArray->SetIndexBuffer(m_Data->QuadIndexBuffer);
        delete[] indices;

        m_Data->QuadPositions = {{
                                                 {-0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, 0.5f, 0.0f, 1.f},
                                                 {-0.5f, 0.5f, 0.0f, 1.f}
                                         }};
    }

    void OpenGLRenderer::InitTriangle()
    {
        m_Data->TriangleVertices = new TriangleVertex[RendererData::MAX_TRIANGLE_VERTICES];
        uint32_t *indices = new uint32_t[RendererData::MAX_TRIANGLE_INDICES];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < RendererData::MAX_TRIANGLE_INDICES; i += 3)
        {
            indices[i] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            offset += 3;
        }
        m_Data->TriangleShader = ShaderLibrary::CreateShader("Triangle",
                                                                     Application::GetInstance()->GetAssetPath(
                                                                             "Panthera/Assets/Shader/Triangle.glsl"));
        m_Data->TriangleVertexArray = VertexArray::Create();
        m_Data->TriangleVertexBuffer = VertexBuffer::Create(
                RendererData::MAX_TRIANGLE_VERTICES * sizeof(TriangleVertex));
        m_Data->TriangleVertexBuffer->SetBufferLayout({
                                                                      {"a_Position", ShaderDataType::Float3},
                                                                      {"a_Color",    ShaderDataType::Float4},
                                                                      {"a_TexCoord", ShaderDataType::Float2},
                                                                      {"a_Index",    ShaderDataType::Float},
                                                                      {"a_Tiling",   ShaderDataType::Float}
                                                              });
        m_Data->TriangleIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_TRIANGLE_INDICES);
        m_Data->TriangleVertexArray->AddVertexBuffer(m_Data->TriangleVertexBuffer);
        m_Data->TriangleVertexArray->SetIndexBuffer(m_Data->TriangleIndexBuffer);
        delete[] indices;

        m_Data->TrianglePositions = {{
                                                     {-0.5f, -0.5f, 0.0f, 1.f},
                                                     {0.5f, -0.5f, 0.0f, 1.f},
                                                     {0.0f, 0.5f, 0.0f, 1.f}
                                             }};
    }

    void OpenGLRenderer::InitCircle()
    {
        m_Data->CircleVertices = new CircleVertex[RendererData::MAX_CIRCLE_VERTICES];

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

        m_Data->CircleShader = ShaderLibrary::CreateShader("FilledCircle",
                                                                   Application::GetInstance()->GetAssetPath(
                                                                           "Panthera/Assets/Shader/FilledCircle.glsl"));

        m_Data->CircleVertexArray = VertexArray::Create();
        m_Data->CircleVertexBuffer = VertexBuffer::Create(
                RendererData::MAX_CIRCLE_VERTICES * sizeof(CircleVertex));
        m_Data->CircleVertexBuffer->SetBufferLayout({
                                                                    {"a_Position", ShaderDataType::Float3},
                                                                    {"a_Center",   ShaderDataType::Float3},
                                                                    {"a_Color",    ShaderDataType::Float4},
                                                                    {"a_Radius",   ShaderDataType::Float},
                                                                    {"a_Border",   ShaderDataType::Float},
                                                                    {"a_TexCoord", ShaderDataType::Float2},
                                                                    {"a_Index",    ShaderDataType::Float},
                                                                    {"a_Tiling",   ShaderDataType::Float}
                                                            });

        m_Data->CircleIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_CIRCLE_INDICES);
        m_Data->CircleVertexArray->AddVertexBuffer(m_Data->CircleVertexBuffer);
        m_Data->CircleVertexArray->SetIndexBuffer(m_Data->CircleIndexBuffer);
        delete[] indices;

        m_Data->CirclePositions = {{
                                                   {-0.5f, -0.5f, 0.0f, 1.f},
                                                   {0.5f, -0.5f, 0.0f, 1.f},
                                                   {0.5f, 0.5f, 0.0f, 1.f},
                                                   {-0.5f, 0.5f, 0.0f, 1.f}
                                           }};
    }

    void OpenGLRenderer::InitLine()
    {
        m_Data->LineVertices = new LineVertex[RendererData::MAX_LINE_VERTICES];

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

        m_Data->LineShader = ShaderLibrary::CreateShader("Line",
                                                                 Application::GetInstance()->GetAssetPath(
                                                                         "Panthera/Assets/Shader/Line.glsl"));

        m_Data->LineVertexArray = VertexArray::Create();
        m_Data->LineVertexBuffer = VertexBuffer::Create(
                RendererData::MAX_LINE_VERTICES * sizeof(LineVertex));
        m_Data->LineVertexBuffer->SetBufferLayout({
                                                                  {"a_Position",              ShaderDataType::Float3},
                                                                  {"a_PosA",                  ShaderDataType::Float3},
                                                                  {"a_PosB",                  ShaderDataType::Float3},
                                                                  {"a_InterpolatingPosition", ShaderDataType::Float2},
                                                                  {"a_Thickness",             ShaderDataType::Float},
                                                                  {"a_Color",                 ShaderDataType::Float4},
                                                          });

        m_Data->LineIndexBuffer = IndexBuffer::Create(indices, RendererData::MAX_LINE_INDICES);
        m_Data->LineVertexArray->AddVertexBuffer(m_Data->LineVertexBuffer);
        m_Data->LineVertexArray->SetIndexBuffer(m_Data->LineIndexBuffer);
        delete[] indices;

        m_Data->LinePositions = {{
                                                 {-0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, -0.5f, 0.0f, 1.f},
                                                 {0.5f, 0.5f, 0.0f, 1.f},
                                                 {-0.5f, 0.5f, 0.0f, 1.f}
                                         }};
    }


    void OpenGLRenderer::Init()
    {
        m_Data = new RendererData;
        m_Data->Textures[0] = Texture2D::Create(Texture2DSpecification{});
        uint32_t textureData = 0xFFFFFFFF;
        m_Data->Textures[0]->SetData(&textureData, sizeof(uint32_t));

        if (!s_CameraUniformBuffer)
        {
            s_CameraUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4), 0);
        }

        InitQuad();
        InitTriangle();
        InitCircle();
        InitLine();

        m_Data->Framebuffer = Framebuffer::Create({
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
        m_Data->Framebuffer->Unbind();
    }

    void OpenGLRenderer::Flush()
    {
        ASSERT(m_Data, "Renderer not initialized!");
        for (uint32_t i = 0; i < m_Data->TextureIndex; i++)
        {
            m_Data->Textures[i]->Bind(i);
        }

        if (m_Data->QuadVerticesCount)
        {
            m_Data->QuadVertexBuffer->AddData(m_Data->QuadVertices,
                                                      m_Data->QuadVerticesCount * sizeof(QuadVertex));


            m_Data->QuadShader->Bind();
            m_Data->QuadVertexArray->Bind();
            DrawIndexed(m_Data->QuadIndicesCount);

            m_Data->QuadIndicesCount = 0;
            m_Data->QuadVerticesCount = 0;
        }

        if (m_Data->TriangleVerticesCount)
        {
            m_Data->TriangleVertexBuffer->AddData(m_Data->TriangleVertices,
                                                          m_Data->TriangleVerticesCount *
                                                          sizeof(TriangleVertex));

            m_Data->TriangleShader->Bind();
            m_Data->TriangleVertexArray->Bind();
            DrawIndexed(m_Data->TriangleIndicesCount);

            m_Data->TriangleIndicesCount = 0;
            m_Data->TriangleVerticesCount = 0;
        }

        if (m_Data->CircleVerticesCount)
        {
            m_Data->CircleVertexBuffer->AddData(m_Data->CircleVertices,
                                                        m_Data->CircleVerticesCount * sizeof(CircleVertex));
            m_Data->CircleShader->Bind();
            m_Data->CircleVertexArray->Bind();
            DrawIndexed(m_Data->CircleIndicesCount);
            m_Data->CircleIndicesCount = 0;
            m_Data->CircleVerticesCount = 0;
        }

        if (m_Data->LineVerticesCount)
        {
            m_Data->LineVertexBuffer->AddData(m_Data->LineVertices,
                                                      m_Data->LineVerticesCount * sizeof(LineVertex));
            m_Data->LineShader->Bind();
            m_Data->LineVertexArray->Bind();
            DrawIndexed(m_Data->LineIndicesCount);
            m_Data->LineIndicesCount = 0;
            m_Data->LineVerticesCount = 0;
        }

        m_Data->TextureIndex = 1;
    }

    static void sBeginScene(RendererData *data, const glm::mat4& projectionMatrix)
    {
        data->QuadIndicesCount = 0;
        data->QuadVerticesCount = 0;
        data->TextureIndex = 1;
        s_CameraUniformBuffer->SetData(&projectionMatrix, sizeof(glm::mat4));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        data->Framebuffer->Bind();
        data->Framebuffer->ClearAttachment(0);
    }

    void OpenGLRenderer::BeginScene()
    {
        static glm::mat4 identity = glm::mat4(1.0f);
        sBeginScene(m_Data, identity);
    }

    void OpenGLRenderer::BeginScene(OrthographicCamera &camera)
    {
        sBeginScene(m_Data, camera.GetViewProjectionMatrix());
    }

    void OpenGLRenderer::EndScene()
    {
        Flush();
        m_Data->Framebuffer->Unbind();
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
        ASSERT(m_Data, "Renderer data is null");
        if (m_Data->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};
        for (uint32_t i = 0; i < 4; i++)
        {
            m_Data->QuadVertices[m_Data->QuadVerticesCount].Position
                    = transform * m_Data->QuadPositions[i];
            m_Data->QuadVertices[m_Data->QuadVerticesCount].Color = color;
            m_Data->QuadVertices[m_Data->QuadVerticesCount].TexCoord = texCoords[i];
            m_Data->QuadVertices[m_Data->QuadVerticesCount].Index = 0;
            m_Data->QuadVertices[m_Data->QuadVerticesCount].TilingFactor = 1.f;
            m_Data->QuadVerticesCount++;
        }

        m_Data->QuadIndicesCount += 6;
    }

    void
    OpenGLRenderer::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color, float tiling, Ref <Texture2D> &texture)
    {
        ASSERT(texture, "Texture is nullptr");
        ASSERT(m_Data, "Renderer data is null");
        if (m_Data->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        bool found = false;
        float index = 0;

        for (uint8_t i = 0; i < m_Data->TextureIndex; i++)
        {
            if (m_Data->Textures[i] == texture)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (m_Data->TextureIndex == RendererData::MAX_TEXTURES && !found)
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
            m_Data->QuadVertices[m_Data->QuadVerticesCount].Position
                    = transform * m_Data->QuadPositions[i];
            m_Data->QuadVertices[m_Data->QuadVerticesCount].Color = color;
            m_Data->QuadVertices[m_Data->QuadVerticesCount].TexCoord = texCoords[i];
            m_Data->QuadVertices[m_Data->QuadVerticesCount].Index = found ? index
                                                                                          : m_Data->TextureIndex;
            m_Data->QuadVertices[m_Data->QuadVerticesCount].TilingFactor = tiling;
            m_Data->QuadVerticesCount++;
        }

        m_Data->QuadIndicesCount += 6;
        if (!found)
        {
            m_Data->Textures[m_Data->TextureIndex] = texture;
            m_Data->TextureIndex++;
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
        ASSERT(m_Data, "Renderer data is null");
        if (m_Data->TriangleVerticesCount + 3 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1}
        };

        for (uint32_t i = 0; i < 3; i++)
        {
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].Position
                    = transform * m_Data->TrianglePositions[i];
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].Color = color;
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].TexCoord = texCoords[i];
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].Index = 0;
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].TilingFactor = 1.f;
            m_Data->TriangleVerticesCount++;
        }

        m_Data->TriangleIndicesCount += 3;
    }

    void OpenGLRenderer::DrawTriangle(const glm::mat4 &transform, const glm::vec4 &color, float tiling,
                                      Ref <Texture2D> &texture)
    {

        if (m_Data->TriangleVerticesCount + 3 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1}
        };

        bool found = false;
        float index = 0;

        for (uint8_t i = 0; i < m_Data->TextureIndex; i++)
        {
            if (m_Data->Textures[i] == texture)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (m_Data->TextureIndex == RendererData::MAX_TEXTURES && !found)
        {
            Flush();
        }

        for (uint32_t i = 0; i < 3; i++)
        {
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].Position
                    = transform * m_Data->TrianglePositions[i];
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].Color = color;
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].TexCoord = texCoords[i];
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].Index = found ? index
                                                                                                  : m_Data->TextureIndex;
            m_Data->TriangleVertices[m_Data->TriangleVerticesCount].TilingFactor = 1.f;
            m_Data->TriangleVerticesCount++;
        }

        m_Data->TriangleIndicesCount += 3;

        if (!found)
        {
            m_Data->Textures[m_Data->TextureIndex] = texture;
            m_Data->TextureIndex++;
        }
    }

#pragma section("Circle")

    void
    OpenGLRenderer::DrawCircle(const glm::vec3 &center, const glm::vec4 &color, float radius, float borderThickness,
                               float fade)
    {
        ASSERT(radius > 0.f, "Radius must be greater than 0")
        ASSERT(borderThickness >= 0.f, "Border thickness must be greater than or equal to 0")
        ASSERT(m_Data, "Renderer data is null")
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
        ASSERT(m_Data, "Renderer data is null")
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
        if (m_Data->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};
        for (uint32_t i = 0; i < 4; i++)
        {
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Position
                    = transform * m_Data->CirclePositions[i];
            m_Data->CircleVertices[m_Data->CircleVerticesCount].InterpolatingPosition =
                    m_Data->CirclePositions[i] * 2.0f; // position between 0 and 1
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Color = color;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Fade = fade;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Border = borderThickness;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].TexCoord = texCoords[i];
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Index = 0;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].TilingFactor = 1.f;
            m_Data->CircleVerticesCount++;
        }

        m_Data->CircleIndicesCount += 6;
    }

    void
    OpenGLRenderer::DrawCircle(const glm::mat4 &transform, const glm::vec4 &color, float borderThickness,
                               float fade, float tiling, Ref <Texture2D> &texture)
    {
        if (m_Data->QuadIndicesCount + 6 > RendererData::MAX_QUAD_INDICES)
        {
            Flush();
        }

        static glm::vec2 texCoords[] = {{0, 0},
                                        {1, 0},
                                        {1, 1},
                                        {0, 1}};

        bool found = false;
        float index = 0;

        for (uint8_t i = 0; i < m_Data->TextureIndex; i++)
        {
            if (m_Data->Textures[i] == texture)
            {
                found = true;
                index = i;
                break;
            }
        }

        if (m_Data->TextureIndex == RendererData::MAX_TEXTURES && !found)
        {
            Flush();
        }

        for (uint32_t i = 0; i < 4; i++)
        {
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Position
                    = transform * m_Data->CirclePositions[i];
            m_Data->CircleVertices[m_Data->CircleVerticesCount].InterpolatingPosition =
                    m_Data->CirclePositions[i] * 2.0f; // position between 0 and 1
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Color = color;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Fade = fade;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Border = borderThickness;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].TexCoord = texCoords[i];
            m_Data->CircleVertices[m_Data->CircleVerticesCount].Index = found ? index
                                                                                              : m_Data->TextureIndex;
            m_Data->CircleVertices[m_Data->CircleVerticesCount].TilingFactor = tiling;
            m_Data->CircleVerticesCount++;
        }

        m_Data->CircleIndicesCount += 6;
        if (!found)
        {
            m_Data->Textures[m_Data->TextureIndex] = texture;
            m_Data->TextureIndex++;
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
            m_Data->LineVertices[m_Data->LineVerticesCount].Position =
                    transform * m_Data->LinePositions[i];
            m_Data->LineVertices[m_Data->LineVerticesCount].InterpolatingPosition =
                    m_Data->LinePositions[i] * 2.0f;
            m_Data->LineVertices[m_Data->LineVerticesCount].PosA = start;
            m_Data->LineVertices[m_Data->LineVerticesCount].PosB = end;
            m_Data->LineVertices[m_Data->LineVerticesCount].Thickness = thickness;
            m_Data->LineVertices[m_Data->LineVerticesCount].Color = color;
            m_Data->LineVerticesCount++;
        }
//
        m_Data->LineIndicesCount += 6;
    }

    Ref <Framebuffer> OpenGLRenderer::GetFramebuffer()
    {
        return m_Data->Framebuffer;
    }

}