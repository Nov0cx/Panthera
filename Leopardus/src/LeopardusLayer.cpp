#include "LeopardusLayer.hpp"
#include <fstream>
#include <portable-file-dialogs.h>

namespace Panthera
{
    LeoparudsLayer::LeoparudsLayer() : Layer()
    {
        /*std::fstream scene = std::fstream("scene.json", std::ios::in);
        if (scene.is_open())
        {
            LOG_DEBUG("Scene file found!")
            m_Scene = SceneSerializer::Deserialize("Test.pscene");
            loadedScene = true;
            LOG_DEBUG("Scene loaded!")
        } else*/
    }

    void LeoparudsLayer::OnStart()
    {
        auto app = Application::GetInstance();
        float aspectRatio = (float) app->GetWindow()->GetWidth() / (float) app->GetWindow()->GetHeight();

        m_Project = new Project("Empty Project ", "", RendererAPI::OpenGL);
        m_Project->AddScene(new Scene(OrthographicCameraController(aspectRatio), "Empty Scene"));

        m_SceneHierarchyPanel = new SceneHierarchyPanel(m_Project->GetActiveScene());

        app->GetWindow()->SetTitle(("Leopardus - " + m_Project->GetActiveScene()->GetName()).c_str());
    }

    void LeoparudsLayer::OnEnd()
    {
        if (m_Project != nullptr)
        {
            if (m_Project->GetScenes().size() > 0 && m_Project->GetPath() != "")
            {
                ProjectSerializer::Serialize(m_Project);
            }
            delete m_Project;
        }
        delete m_SceneHierarchyPanel;
    }

    void LeoparudsLayer::OnUpdate(Timestep ts)
    {
        m_Project->GetActiveScene()->OnUpdate(ts);
    }

    void LeoparudsLayer::OnEvent(Event &e)
    {
        m_Project->GetActiveScene()->OnEvent(e);
    }

    LeoparudsLayer::~LeoparudsLayer()
    {

    }

    void LeoparudsLayer::OnImGuiRender()
    {
        RenderMenu();
        m_Project->GetActiveScene()->OnImGuiRender();
        m_SceneHierarchyPanel->Render();
    }

    void LeoparudsLayer::RenderMenu()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save Scene"))
                {
                    //SceneSerializer::Serialize(*m_Project->GetActiveScene(), "Test.pscene");
                }
                if (ImGui::MenuItem("Reload Scene"))
                {
                    //m_Project->GetActiveScene() = SceneSerializer::Deserialize("Test.pscene");
                    LOG_DEBUG("Scene loaded!")
                }
                /*if (ImGui::MenuItem("Open Scene"))
                {
                    auto selection = pfd::open_file("Open Scene", Application::GetInstance()->GetExePath(), {"Panthera Scenes (*.pscene)", "*.pscene"}).result();
                    for (auto& file : selection)
                    {
                        m_Scene = SceneSerializer::Deserialize(file);
                        LOG_DEBUG("Scene loaded!")
                        break;
                    }
                    Application::GetInstance()->GetWindow()->SetTitle(("Leopardus - " + m_Scene->GetName()).c_str());
                }*/
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
}