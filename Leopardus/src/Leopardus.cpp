#include "Panthera/Panthera.hpp"

#include <fstream>

class LeopardusLayer : public Panthera::Layer
{
public:
    LeopardusLayer() : Panthera::Layer()
    {
        m_CameraController = Panthera::OrthographicCameraController(1.33);
        std::fstream scene = std::fstream("scene.json", std::ios::in);
        if (scene.is_open())
        {
            LOG_INFO("Scene file found!");
            m_Scene = Panthera::SceneSerializer::Deserialize("scene.json");
            loadedScene = true;
            LOG_INFO("Scene loaded!");
        } else
        {
            m_Scene = new Panthera::Scene(&m_CameraController.GetCamera());
        }
    }

    ~LeopardusLayer()
    {

    }

    virtual void OnStart() override
    {
        if (!loadedScene)
        {
            Panthera::Texture2DSpecification spec{
                    .Path = Panthera::Application::GetInstance()->GetAssetPath(
                            "Panthera/Assets/Textures/color.jpg").c_str(),
                    .InternalFormat = Panthera::Texture2DInternalFormat::RGB8,
                    .DataFormat = Panthera::Texture2DDataFormat::RGB,
            };
            m_ColorTexture = Panthera::Texture2D::Create(spec);
            Panthera::Texture2DSpecification spec2{
                    .Path = Panthera::Application::GetInstance()->GetAssetPath(
                            "Panthera/Assets/Textures/flower.jpg").c_str(),
                    .InternalFormat = Panthera::Texture2DInternalFormat::RGB8,
                    .DataFormat = Panthera::Texture2DDataFormat::RGB,
            };
            m_FlowerTexture = Panthera::Texture2D::Create(spec2);
            Panthera::Texture2DSpecification spec3{
                    .Path = Panthera::Application::GetInstance()->GetAssetPath(
                            "Panthera/Assets/Textures/form.jpg").c_str(),
                    .InternalFormat = Panthera::Texture2DInternalFormat::RGB8,
                    .DataFormat = Panthera::Texture2DDataFormat::RGB,
            };
            m_FormTexture = Panthera::Texture2D::Create(spec3);
            {
                Panthera::SceneEntity entity = m_Scene->CreateEntity("Quad1");
                entity.CreateComponent<Panthera::QuadComponent>(
                        Panthera::QuadComponent({1.0, 1.0, 1.0, 1.0}, 1.0f, m_FormTexture));
                entity.CreateComponent<Panthera::TransformComponent>(
                        Panthera::TransformComponent({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}));
            }
            {
                Panthera::SceneEntity entity = m_Scene->CreateEntity("Circle1");
                entity.CreateComponent<Panthera::CircleComponent>(
                        Panthera::CircleComponent({1.0, 1.0, 1.0, 1.0}, 0.0f, 0.01f, 1.0f, m_ColorTexture));
                entity.CreateComponent<Panthera::TransformComponent>(
                        Panthera::TransformComponent({1.2, 1.2, 0.}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}));
            }
            {
                Panthera::SceneEntity entity = m_Scene->CreateEntity("Triangle1");
                entity.CreateComponent<Panthera::TriangleComponent>(
                        Panthera::TriangleComponent({1.0, 1.0, 1.0, 1.0}, 1.0f, m_FlowerTexture));
                entity.CreateComponent<Panthera::TransformComponent>(
                        Panthera::TransformComponent({-1.2, -1.2, 0.}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}));
            }
            {
                Panthera::SceneEntity entity = m_Scene->CreateEntity("Line1");
                entity.CreateComponent<Panthera::LineComponent>(
                        Panthera::LineComponent({1.0, .0, 1.0, 1.0}, 0.0f));
                entity.CreateComponent<Panthera::LineTransformComponent>(
                        Panthera::LineTransformComponent({-1.2, -1.2, 0.}, {2.2, 1.2, 0.0}));
            }
        }

    }

    virtual void OnEnd() override
    {
        LOG_INFO("Scene destroyed!");
        Panthera::SceneSerializer::Serialize(*m_Scene, "scene.json");
        delete m_Scene;
    }

    virtual void OnUpdate(Panthera::Timestep ts) override
    {
        m_CameraController.OnUpdate(ts);
        m_Scene->OnUpdate(ts);
    }

    virtual void OnEvent(Panthera::Event &e) override
    {
        m_CameraController.OnEvent(e);
    }

private:
    Panthera::Ref <Panthera::Texture2D> m_ColorTexture, m_FlowerTexture, m_FormTexture;
    Panthera::OrthographicCameraController m_CameraController;
    Panthera::Scene *m_Scene;
    bool loadedScene = false;
};

class Leopardus : public Panthera::Application
{
public:
    Leopardus(const Panthera::AppProps &props) : Panthera::Application(props)
    {
        auto layer = Panthera::CreateRef<LeopardusLayer>();
        GetLayerStack()->PushLayout(layer);
    }
};

int main(int argc, char **argv)
{
    Panthera::ProgramArgs args(argc, argv);
    Panthera::AppProps props(args, "Leopardus", 1920, 1080, false);
    Leopardus app(props);

    app.Run();
    return 0;
}