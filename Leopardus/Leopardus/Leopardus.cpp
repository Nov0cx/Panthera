#include "Panthera/Panthera.hpp"

#include "Panthera/Core/Entry.hpp"

#include <glad/glad.h>

namespace Panthera
{
    class Leopardus : public Layer
    {
    public:
        Leopardus() : Layer()
        {
        }

        void OnEnable() override
        {
            m_Shader = ShaderLibrary::Load(AssetLoader::GetAssetPath("Panthera/assets/shader/FlatColor.glsl"));

            float vertices[] = {
                    -0.5f, -0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    0.0f, 0.5f, 0.0f
            };
            m_VertexArray = VertexArray::Create();
            Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(float) * 3 * 3);
            vertexBuffer->SetBufferLayout({
                                                  {ShaderDataType::Float3, "a_Position"}
                                          });

            uint32_t indices[] = {
                    0, 1, 2
            };
            Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, 3);
            m_VertexArray->AddVertexBuffer(vertexBuffer);
            m_VertexArray->SetIndexBuffer(indexBuffer);
            Ref<UniformBuffer> uniformBuffer = UniformBuffer::Create(sizeof(glm::vec4), 0);
            glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};
            uniformBuffer->SetData(&color, sizeof(glm::vec4), 0);
        }

        void OnDisable() override
        {

        }

        void OnUpdate(Timestep ts) override
        {
            GlobalRenderer::SubmitFunc([]() {
                GlobalRenderer::GetMainWindow()->GetRenderContext()->Clear({0.2f, 0.2f, 0.2f, 1.0f});
            });
            GlobalRenderer::SubmitFunc([this](){
                m_Shader->Bind();
                m_VertexArray->Bind();
                glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            });
        }

    private:
        Ref<VertexArray> m_VertexArray;
        Ref<Shader> m_Shader;
    };

    void ApplicationCreationCallback(ApplicationInfo *outInfo)
    {
        outInfo->Name = "Leopardus";
        outInfo->Version = {0, 3, 0};
        outInfo->Width = 500;
        outInfo->Height = 500;
    }

    int Main(Application *app)
    {
        app->PushLayer(new Leopardus());
        app->Run();

        return 0;
    }
}