#include "LeopardusLayer.hpp"
#include <fstream>

namespace Panthera
{
    LeoparudsLayer::LeoparudsLayer() : Layer()
    {
        auto app = Application::GetInstance();
        float aspectRatio = (float) app->GetWindow()->GetWidth() / (float) app->GetWindow()->GetHeight();
        std::fstream scene = std::fstream("scene.json", std::ios::in);
        if (scene.is_open())
        {
            LOG_DEBUG("Scene file found!")
            m_Scene = SceneSerializer::Deserialize("Test.pscene");
            loadedScene = true;
            LOG_DEBUG("Scene loaded!")
        } else
        {
            m_Scene = new Scene(OrthographicCameraController(aspectRatio), "Test");
        }
        m_SceneHierarchyPanel = new SceneHierarchyPanel(m_Scene);
        app->GetWindow()->SetTitle(("Leopardus - " + m_Scene->GetName()).c_str());
    }

    void LeoparudsLayer::OnStart()
    {
        if (!loadedScene)
        {
            Texture2DSpecification spec{
                    .Path = Application::GetInstance()->GetAssetPath(
                            "Panthera/Assets/Textures/color.jpg").c_str(),
                    .InternalFormat = Texture2DInternalFormat::RGB8,
                    .DataFormat = Texture2DDataFormat::RGB,
            };
            m_ColorTexture = Texture2D::Create(spec);
            Texture2DSpecification spec2{
                    .Path = Application::GetInstance()->GetAssetPath(
                            "Panthera/Assets/Textures/flower.jpg").c_str(),
                    .InternalFormat = Texture2DInternalFormat::RGB8,
                    .DataFormat = Texture2DDataFormat::RGB,
            };
            m_FlowerTexture = Texture2D::Create(spec2);
            Texture2DSpecification spec3{
                    .Path = Application::GetInstance()->GetAssetPath(
                            "Panthera/Assets/Textures/form.jpg").c_str(),
                    .InternalFormat = Texture2DInternalFormat::RGB8,
                    .DataFormat = Texture2DDataFormat::RGB,
            };
            m_FormTexture = Texture2D::Create(spec3);
            {
                SceneEntity entity = m_Scene->CreateEntity("Quad1");
                entity.CreateComponent<QuadComponent>(
                        QuadComponent({1.0, 1.0, 1.0, 1.0}, 1.0f, m_FormTexture));
                entity.CreateComponent<TransformComponent>(
                        TransformComponent({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}));
            }
            {
                SceneEntity entity = m_Scene->CreateEntity("Circle1");
                entity.CreateComponent<CircleComponent>(
                        CircleComponent({1.0, 1.0, 1.0, 1.0}, 0.0f, 0.01f, 1.0f, m_ColorTexture));
                entity.CreateComponent<TransformComponent>(
                        TransformComponent({1.2, 1.2, 0.}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}));
            }
            {
                SceneEntity entity = m_Scene->CreateEntity("Triangle1");
                entity.CreateComponent<TriangleComponent>(
                        TriangleComponent({1.0, 1.0, 1.0, 1.0}, 1.0f, m_FlowerTexture));
                entity.CreateComponent<TransformComponent>(
                        TransformComponent({-1.2, -1.2, 0.}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}));
            }
            {
                SceneEntity entity = m_Scene->CreateEntity("Line1");
                entity.CreateComponent<LineComponent>(
                        LineComponent({1.0, .0, 1.0, 1.0}, 0.0f));
                entity.CreateComponent<LineTransformComponent>(
                        LineTransformComponent({-1.2, -1.2, 0.}, {2.2, 1.2, 0.0}));
            }
        }
    }

    void LeoparudsLayer::OnEnd()
    {
        LOG_DEBUG("Scene destroyed!")
        SceneSerializer::Serialize(*m_Scene, "Test.pscene");
        delete m_Scene;
        delete m_SceneHierarchyPanel;
    }

    void LeoparudsLayer::OnUpdate(Timestep ts)
    {
        m_Scene->OnUpdate(ts);
    }

    void LeoparudsLayer::OnEvent(Event &e)
    {
        m_Scene->OnEvent(e);
    }

    LeoparudsLayer::~LeoparudsLayer()
    {

    }

    void LeoparudsLayer::OnImGuiRender()
    {
        m_Scene->OnImGuiRender();
        m_SceneHierarchyPanel->Render();
    }
}