#include "ProjectPanel.hpp"

namespace Panthera
{

    ProjectPanel::ProjectPanel()
    {}

    ProjectPanel::~ProjectPanel()
    {}

    void ProjectPanel::Render(Ref <Project> &project)
    {
        ImGui::Begin(("Project: " + project->GetName()).c_str());

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

        ImGui::End();
    }
}