#include "ProjectPanel.hpp"

#include <portable-file-dialogs.h>

namespace Panthera
{

    ProjectPanel::ProjectPanel()
    {}

    ProjectPanel::~ProjectPanel()
    {}

    void ProjectPanel::Render(Ref <Project> &project)
    {
        ImGui::Begin("Project Panel");

        std::string name = project->GetName();
        char nameBuffer[256];
        memset(nameBuffer, 0, sizeof(nameBuffer));
        std::strncpy(nameBuffer, name.c_str(), sizeof(nameBuffer));
        if (ImGui::InputText("Current Project", nameBuffer, sizeof(nameBuffer)))
        {
            if (strlen(nameBuffer) > 0)
                name = std::string(nameBuffer);
        }
        project->SetName(name);
        ImGui::Separator();

        std::string path = project->GetPath();
        if (ImGui::Selectable(("Path: " + path).c_str()))
        {
            auto selection = pfd::select_folder("Select Scene Path", path == "" ? Application::GetInstance()->GetCurrentPath() : path).result();
            if (!selection.empty())
            {
                path = selection + "/" + name + ".pproject";
            }
        }
        project->SetPath(path);
        ImGui::Separator();

        const char* items[] = {"None", "OpenGL", "Vulkan", "Direct X", "Metal", "OpenGL ES"};
        if (ImGui::BeginCombo("Renderer API", items[(int)project->GetRendererAPI()], ImGuiComboFlags_None))
        {
            for (int i = 0; i < IM_ARRAYSIZE(items); i++)
            {
                bool is_selected = (project->GetRendererAPI() == static_cast<RendererAPI>(i));
                if (ImGui::Selectable(items[i], is_selected))
                {
                    project->SetRendererAPI(static_cast<RendererAPI>(i));
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        auto scenes = project->GetScenes();
        std::vector<const char *> sceneNames = {};

        for (auto scene : scenes)
        {
            sceneNames.push_back(scene->GetName().c_str());
        }

        if (ImGui::BeginCombo("Active Scene", project->GetActiveScene()->GetName().c_str(), ImGuiComboFlags_None))
        {
            for (int i = 0; i < sceneNames.size(); i++)
            {
                bool is_selected = (project->GetActiveScene() == scenes[i]);
                if (ImGui::Selectable(sceneNames[i], is_selected))
                {
                    project->SetActiveScene(sceneNames[i]);
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::Separator();

        ImGui::End();
    }
}