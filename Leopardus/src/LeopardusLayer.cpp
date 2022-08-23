#include "LeopardusLayer.hpp"

namespace Panthera
{
    Leoparuds::Leoparuds()
    {
        auto app = Panthera::Application::GetInstance();
        float aspectRatio = (float) app->GetWindow()->GetWidth() / (float) app->GetWindow()->GetHeight();
        m_CameraController = Panthera::OrthographicCameraController(aspectRatio);
        std::fstream scene = std::fstream("scene.json", std::ios::in);
        if (scene.is_open())
        {
            LOG_DEBUG("Scene file found!")
            m_Scene = Panthera::SceneSerializer::Deserialize("scene.json");
            loadedScene = true;
            LOG_DEBUG("Scene loaded!")
        } else
        {
            m_Scene = new Panthera::Scene(&m_CameraController.GetCamera());
        }
    }

    void Leoparuds::OnStart()
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

    void Leoparuds::OnEnd()
    {
        LOG_DEBUG("Scene destroyed!")
        Panthera::SceneSerializer::Serialize(*m_Scene, "scene.json");
        delete m_Scene;
    }

    void Leoparuds::OnUpdate(Panthera::Timestep ts)
    {
        m_CameraController.OnUpdate(ts);
        m_Scene->OnUpdate(ts);
    }

    void Leoparuds::OnEvent(Panthera::Event &e)
    {
        m_CameraController.OnEvent(e);
    }
}