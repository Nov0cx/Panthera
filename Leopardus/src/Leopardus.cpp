#include "Panthera/Panthera.hpp"

class LeopardusLayer : public Panthera::Layer
{
public:
    LeopardusLayer() : Panthera::Layer()
    {}

    virtual void OnStart() override
    {
        m_Renderer = Panthera::Renderer::CreateRenderer();
        m_Renderer->Init();
        m_Texture = Panthera::Texture2D::Create(Panthera::Application::GetInstance()->GetAssetPath("Panthera/Assets/Textures/flower.jpg"));
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

        auto vertexArray2 = Panthera::VertexArray::Create();

        uint32_t indices2[6] = {
                0, 1, 2,
                2, 3, 0
        };

        glm::vec4 color2 = {0.6, 0.3, 0.05, 1.};

        glm::vec3 rightBottom2 = glm::vec3(0.5, -0.5, 0.0f) + glm::vec3(1.0f, 1.0f, .0f);
        glm::vec3 leftBottom2 = glm::vec3(-0.5, -0.5, 0.0f) + glm::vec3(1.0f, 1.0f, .0f);
        glm::vec3 rightTop2 = glm::vec3(0.5, 0.5, 0.0f) + glm::vec3(1.0f, 1.0f, .0f);
        glm::vec3 leftTop2 = glm::vec3(-0.5, 0.5, 0.0f) + glm::vec3(1.0f, 1.0f, .0f);

        float positions2[3 * 4 * 4] = {
                leftBottom2.x, leftBottom2.y, leftBottom2.z, color2.x, color2.y, color2.z, color2.w, 0, 1, 0,
                rightBottom2.x, rightBottom2.y, rightBottom2.z, color2.x, color2.y, color2.z, color2.w, 0, 1, 0,
                rightTop2.x, rightTop2.y, rightTop2.z, color2.x, color2.y, color2.z, color2.w, 0, 1, 0,
                leftTop2.x, leftTop2.y, leftTop2.z, color2.x, color2.y, color2.z, color2.w, 0, 1, 0,
        };

        auto shader2 = Panthera::ShaderLibrary::GetShader("Texture");


        auto vb2 = Panthera::VertexBuffer::Create(positions, sizeof(positions2));
        vb2->SetBufferLayout({
                                    {"a_Position", Panthera::ShaderDataType::Float3},
                                    {"a_Color", Panthera::ShaderDataType::Float4},
                                    {"a_TexCoord", Panthera::ShaderDataType::Float2},
                                    {"a_TexIndex", Panthera::ShaderDataType::Int}
                            });
        vertexArray2->AddVertexBuffer(vb2);
        auto ib2 = Panthera::IndexBuffer::Create(indices, sizeof(indices2) / sizeof(uint32_t));
        vertexArray2->SetIndexBuffer(ib2);

        m_Texture->Bind(0);
        shader2->Bind();
        m_Renderer->DrawIndexed(vertexArray2);
    }

    virtual void OnEvent(Panthera::Event &e) override
    {

    }

private:
    Panthera::Renderer *m_Renderer;
    Panthera::Ref<Panthera::Texture2D> m_Texture;
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
    auto shader = Panthera::ShaderLibrary::CreateShader("FlatColor", path);

    auto textureShaderPath = app.GetAssetPath("Panthera/Assets/Shader/Texture.glsl");
    auto textureShader = Panthera::ShaderLibrary::CreateShader("Texture", textureShaderPath);

    app.Run();
    return 0;
}