#include "OpenGLRenderer.hpp"

#include <glad/glad.h>
#include "Panthera/Render/VertexArray/VertexArray.hpp"
#include "Panthera/Render/Texture/Texture.hpp"
#include "Panthera/Render/Shader/Shader.hpp"
#include "Panthera/Render/Buffer/VertexBuffer.hpp"
#include "Panthera/Render/Buffer/IndexBuffer.hpp"
#include "Panthera/Core/Pointer.hpp"
#include "Panthera/Core/Log.hpp"

namespace Panthera
{

    OpenGLRenderer::OpenGLRenderer()
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    void OpenGLRenderer::Init()
    {
    }

    void OpenGLRenderer::Clear(glm::vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawIndexed(const Ref <VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        vertexArray->GetIndexBuffer()->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::DrawQuad(glm::vec3 center, glm::vec2 size, glm::vec4 color)
    {
        glm::vec3 rightBottom = center + glm::vec3(size.x / 2, -size.y / 2, 0.f);
        glm::vec3 leftBottom = center + glm::vec3(-size.x / 2, -size.y / 2, 0.f);
        glm::vec3 rightTop = center + glm::vec3(size.x / 2, size.y / 2, 0.f);
        glm::vec3 leftTop = center + glm::vec3(-size.x / 2, size.y / 2, 0.f);

        float positions[] = {
                leftBottom.x, leftBottom.y, leftBottom.z, color.x, color.y, color.z, color.w,
                rightBottom.x, rightBottom.y, rightBottom.z, color.x, color.y, color.z, color.w,
                rightTop.x, rightTop.y, rightTop.z, color.x, color.y, color.z, color.w,
                leftTop.x, leftTop.y, leftTop.z, color.x, color.y, color.z, color.w,
        };

        uint32_t indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        auto vertexArray = VertexArray::Create();
        auto vb = VertexBuffer::Create(positions, sizeof(positions));
        vb->SetBufferLayout({
                                    {"a_Position", ShaderDataType::Float3},
                                    {"a_Color",    ShaderDataType::Float4}
                            });
        auto ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        auto shader = ShaderLibrary::GetShader("FlatColor");
        vertexArray->AddVertexBuffer(vb);
        vertexArray->SetIndexBuffer(ib);

        shader->Bind();
        DrawIndexed(vertexArray);
    }

    void OpenGLRenderer::DrawQuad(glm::vec2 center, glm::vec2 size, glm::vec4 color)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color);
    }

    void
    OpenGLRenderer::DrawQuad(glm::vec3 center, glm::vec2 size, glm::vec4 color, uint8_t index, Ref <Texture2D> &texture)
    {
        glm::vec3 rightBottom = center + glm::vec3(size.x / 2, -size.y / 2, 0.f);
        glm::vec3 leftBottom = center + glm::vec3(-size.x / 2, -size.y / 2, 0.f);
        glm::vec3 rightTop = center + glm::vec3(size.x / 2, size.y / 2, 0.f);
        glm::vec3 leftTop = center + glm::vec3(-size.x / 2, size.y / 2, 0.f);

        float positions[] = {
                leftBottom.x, leftBottom.y, leftBottom.z, color.x, color.y, color.z, color.w, 0, 0, (float) index,
                rightBottom.x, rightBottom.y, rightBottom.z, color.x, color.y, color.z, color.w, 1, 0, (float) index,
                rightTop.x, rightTop.y, rightTop.z, color.x, color.y, color.z, color.w, 1, 1, (float) index,
                leftTop.x, leftTop.y, leftTop.z, color.x, color.y, color.z, color.w, 0, 1, (float) index
        };
        uint32_t indices[6] = {
                0, 1, 2,
                2, 3, 0
        };
        auto vertexArray = VertexArray::Create();
        auto vertexBuffer = VertexBuffer::Create(positions, sizeof(positions));
        vertexBuffer->SetBufferLayout({
                                              {"a_Position", ShaderDataType::Float3},
                                              {"a_Color",    ShaderDataType::Float4},
                                              {"a_TexCoord", ShaderDataType::Float2},
                                              {"a_Index",    ShaderDataType::Int}
                                      });
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        auto shader = ShaderLibrary::GetShader("Texture");
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        shader->Bind();
        texture->Bind(index);
        DrawIndexed(vertexArray);
    }

    void
    OpenGLRenderer::DrawQuad(glm::vec2 center, glm::vec2 size, glm::vec4 color, uint8_t index, Ref <Texture2D> &texture)
    {
        DrawQuad(glm::vec3(center.x, center.y, 0.f), size, color, index, texture);
    }
}