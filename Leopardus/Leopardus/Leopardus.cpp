#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"

#include <glad/glad.h>

namespace Panthera
{
    void ApplicationCreationCallback(ApplicationInfo *outInfo)
    {
        outInfo->Name = "Leopardus";
        outInfo->Version = {0, 3, 0};
        outInfo->Width = 500;
        outInfo->Height = 500;
    }

    int Main(Application *app)
    {
        WindowInfo windowInfo;
        windowInfo.Title = app->GetInfo().Name + " - " + app->GetInfo().Version.ToString();
        windowInfo.Width = app->GetInfo().Width;
        windowInfo.Height = app->GetInfo().Height;
        windowInfo.VSync = false;

        GlobalRenderer::Init(windowInfo);

        Ref<Shader> shader = ShaderLibrary::Load(AssetLoader::GetAssetPath("Panthera/assets/shader/FlatColor.glsl"));

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        Ref<VertexArray> vertexArray = VertexArray::Create();
        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(float) * 3 * 3);
        vertexBuffer->SetBufferLayout({
            {ShaderDataType::Float3, "a_Position"}
        });

        uint32_t indices[] = {
            0, 1, 2
        };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 3);
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<UniformBuffer> uniformBuffer = UniformBuffer::Create(sizeof(glm::vec4), 0);
        glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};
        uniformBuffer->SetData(&color, sizeof(glm::vec4), 0);

        while (!GlobalRenderer::ShutdownAllowed())
        {
            GlobalRenderer::BeginFrame();
            GlobalRenderer::SubmitFunc([]() {
                GlobalRenderer::GetMainWindow()->GetRenderContext()->Clear({0.2f, 0.2f, 0.2f, 1.0f});
            });
            GlobalRenderer::SubmitFunc([vertexArray, shader](){
                shader->Bind();
                vertexArray->Bind();
                glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            });
            GlobalRenderer::SubmitFunc([]() {
                GlobalRenderer::GetMainWindow()->Update();
            });
            GlobalRenderer::EndFrame();
        }

        GlobalRenderer::Shutdown();

        return 0;
    }
}