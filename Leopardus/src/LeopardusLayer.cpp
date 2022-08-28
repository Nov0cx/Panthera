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

        app->GetWindow()->SetTitle(("Leopardus - " + m_Project->GetName() + " - " + m_Project->GetActiveScene()->GetName()).c_str());
    }

    void LeoparudsLayer::OnEnd()
    {
        SaveProject();
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
        ASSERT(m_Project != nullptr, "Project is null!");
        ASSERT(m_Project->GetActiveScene() != nullptr, "Scene is null!");
        m_Project->GetActiveScene()->OnImGuiRender();
        m_SceneHierarchyPanel->Render(m_Project->GetActiveScene());
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
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("New Project"))
                {
                    SaveProject();
                    auto selection = pfd::select_folder("New Project", Application::GetInstance()->GetExePath()).result();
                    LOG_DEBUG("New Project: " + selection);
                    if (!selection.empty())
                    {
                        std::string path = selection + "/.pproject";
                        LOG_DEBUG("Path: " + path);
                        m_Project = new Project("New Project", path, RendererAPI::OpenGL);
                        LOG_DEBUG("Project created!");
                        ASSERT(m_Project != nullptr, "Project is null!");
                        if (m_Project->GetActiveScene() == nullptr)
                        {
                            LOG_DEBUG("No scene found!");
                            m_Project->AddScene(new Scene(OrthographicCameraController(Application::GetInstance()->GetWindow()->GetWidth() / (float) Application::GetInstance()->GetWindow()->GetHeight()), "New Scene"));
                        }
                        Application::GetInstance()->GetWindow()->SetTitle(("Leopardus - " + m_Project->GetName() + " - "  + m_Project->GetActiveScene()->GetName()).c_str());
                    }
                }
                if (ImGui::MenuItem("Open Project"))
                {
                    SaveProject();
                    auto selection = pfd::open_file("Open Project", Application::GetInstance()->GetExePath(), {"Panthera Projects (*.pproject)", "*.pproject"}).result();
                    for (auto& file : selection)
                    {
                        LOG_DEBUG("Project found: " + file);
                        m_Project = ProjectSerializer::Deserialize(file);
                        LOG_DEBUG("Project loaded!")
                        ASSERT(m_Project != nullptr, "Project is null!");
                        Application::GetInstance()->GetWindow()->SetTitle(("Leopardus - " + m_Project->GetName() + " - " + m_Project->GetActiveScene()->GetName()).c_str());
                        break;
                    }
                }
                if (ImGui::MenuItem("Save Project"))
                {
                    SaveProject();
                }
                if (ImGui::MenuItem("Add Scene"))
                {
                    auto selection = pfd::open_file("Add Scene", Application::GetInstance()->GetExePath(), {"Panthera Scenes (*.pscene)", "*.pscene"}).result();
                    for (auto& file : selection)
                    {
                        LOG_DEBUG("Scene found: " + file);
                        m_Project->AddScene(SceneSerializer::Deserialize(file));
                        break;
                    }
                }
                /*if (ImGui::MenuItem("Set Active Scene"))
                {

                }*/
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }

    void LeoparudsLayer::SaveProject()
    {
        if (m_Project != nullptr)
        {
            if (m_Project->GetScenes().size() > 0 && m_Project->GetPath() != "")
            {
                ProjectSerializer::Serialize(m_Project);
            }
            delete m_Project;
        }
    }
}