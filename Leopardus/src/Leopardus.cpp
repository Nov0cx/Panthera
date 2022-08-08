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
        m_Texture = Panthera::Texture2D::Create(Panthera::Application::GetInstance()->GetAssetPath("Panthera/Assets/Textures/color.jpg"));
    }

    virtual void OnEnd() override
    {
        delete m_Renderer;
    }

    virtual void OnUpdate(Panthera::Timestep ts) override
    {
        m_Renderer->Clear();
        m_Renderer->DrawQuad({-0.3f, -0.3f, 0.0f}, {0.6f, 0.6f}, {1.0f, 0.0f, 0.0f, 1.0f});
        m_Renderer->DrawQuad({0.3f, 0.3f, 0.0f}, {0.6f, 0.6f}, {1.0f, 1.0f, 1.0f, 1.0f}, 0, m_Texture);
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