#include "Panthera/Panthera.hpp"
#include <fstream>

class LeopardusLayer : public Panthera::Layer
{
public:
    LeopardusLayer() : Panthera::Layer()
    {}

    virtual void OnStart() override
    {
        if (m_Renderer)
            delete m_Renderer;
        m_Renderer = Panthera::Renderer::CreateRenderer();
        m_Renderer->Init();
    }

    virtual void OnEnd() override
    {
        delete m_Renderer;
    }

    virtual void OnUpdate(Panthera::Timestep ts) override
    {
        auto vertexArray = Panthera::VertexArray::Create();

        uint32_t indices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        glm::vec4 color = {0.6, 0.3, 0.05, 1.};

        glm::vec3 rightBottom = glm::vec3(0.5, -0.5, 0.0f);
        glm::vec3 leftBottom = glm::vec3(-0.5, -0.5, 0.0f);
        glm::vec3 rightTop = glm::vec3(0.5, 0.5, 0.0f);
        glm::vec3 leftTop = glm::vec3(-0.5, 0.5, 0.0f);

        float positions[3 * 4 * 4] = {
                leftBottom.x, leftBottom.y, leftBottom.z, color.x, color.y, color.z, color.w,
                rightBottom.x, rightBottom.y, rightBottom.z, color.x, color.y, color.z, color.w,
                rightTop.x, rightTop.y, rightTop.z, color.x, color.y, color.z, color.w,
                leftTop.x, leftTop.y, leftTop.z, color.x, color.y, color.z, color.w,
        };

        auto shader = Panthera::ShaderLibrary::GetShader("FlatColor");
        shader->Bind();

        auto vb = Panthera::VertexBuffer::Create(positions, sizeof(positions));
        vb->SetBufferLayout({
                                    {"a_Position", Panthera::ShaderDataType::Float3},
                                    {"a_Color",    Panthera::ShaderDataType::Float4}
                            });
        vertexArray->AddVertexBuffer(vb);
        auto ib = Panthera::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        vertexArray->SetIndexBuffer(ib);

        m_Renderer->Clear();
        m_Renderer->DrawIndexed(vertexArray);
    }

    virtual void OnEvent(Panthera::Event &e) override
    {

    }

private:
    Panthera::Renderer *m_Renderer;
};

class Leopardus : public Panthera::Application
{
public:
    Leopardus(const Panthera::AppProps &props) : Panthera::Application(props)
    {
        auto layer = Panthera::CreateRef<LeopardusLayer>();
        GetLayerStack()->PushLayer(layer);
    }
};

int main(int argc, char **argv)
{
    Panthera::ProgramArgs args(argc, argv);
    Panthera::AppProps props(args, "Leopardus", 800, 600, false);
    Leopardus app(props);
    auto path = app.GetAssetPath("Panthera/Assets/Shader/FlatColor.glsl");
    LOG_INFO("{}", path);
    auto shader = Panthera::ShaderLibrary::CreateShader("FlatColor", path);


    app.Run();
    return 0;
}