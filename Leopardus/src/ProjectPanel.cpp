#include "ProjectPanel.hpp"

namespace Panthera
{

    ProjectPanel::ProjectPanel()
    {}

    ProjectPanel::~ProjectPanel()
    {}

    void ProjectPanel::Render(Ref <Project> &project)
    {
        ImGui::Begin("Project Panel");
        ImGui::Text("Project: %s", project->GetName().c_str());
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

        ImGui::End();
    }
}