#include "Panthera/Panthera.hpp"

class LeopardusLayer : public Panthera::Layer
{
public:
    LeopardusLayer() : Panthera::Layer()
    {
        m_CameraController = Panthera::OrthographicCameraController(1.33);
    }

    virtual void OnStart() override
    {
        m_Renderer = Panthera::Renderer::CreateRenderer();
        m_Renderer->Init();
        m_ColorTexture = Panthera::Texture2D::Create(Panthera::Application::GetInstance()->GetAssetPath("Panthera/Assets/Textures/color.jpg"));
        m_FlowerTexture = Panthera::Texture2D::Create(Panthera::Application::GetInstance()->GetAssetPath("Panthera/Assets/Textures/flower.jpg"));
    }

    virtual void OnEnd() override
    {
        delete m_Renderer;
    }

    virtual void OnUpdate(Panthera::Timestep ts) override
    {
        m_CameraController.OnUpdate(ts);
        m_Renderer->Clear();
        m_Renderer->BeginScene(m_CameraController.GetCamera());
        m_Renderer->DrawQuad({-0.3f, -0.3f, 0.0f}, {0.6f, 0.6f}, {1.0f, 0.0f, 0.0f, 1.0f});
        m_Renderer->DrawQuad({0.3f, 0.3f, 0.0f}, {0.6f, 0.6f}, {1.0f, 1.0f, 1.0f, 1.0f}, 1.f, m_ColorTexture);
        m_Renderer->DrawQuad({-0.37f, 0.37f, 0.0f}, {0.63f, 0.63f}, glm::radians(36.f), {1.0f, 1.0f, 1.0f, 0.8f}, 1.f, m_FlowerTexture);
        m_Renderer->DrawTriangle({.3f, -0.3f, 0.0f}, {0.6f, 0.6f},  -glm::radians(36.f), {1.0f, 1.0f, 1.0f, 0.6f}, 1.f, m_FlowerTexture);
        m_Renderer->DrawCircle({-0.8f, -0.8f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 0.3f, 0.3f, 0.4f);
        m_Renderer->DrawCircle({0.8f, -0.8f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 0.3f, 0.4f, 0.02f, 1.f, m_ColorTexture);
        m_Renderer->EndScene();
    }

    virtual void OnEvent(Panthera::Event &e) override
    {
        m_CameraController.OnEvent(e);
    }

private:
    Panthera::Renderer *m_Renderer;
    Panthera::Ref<Panthera::Texture2D> m_ColorTexture, m_FlowerTexture;
    Panthera::OrthographicCameraController m_CameraController;
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

    app.Run();
    return 0;
}