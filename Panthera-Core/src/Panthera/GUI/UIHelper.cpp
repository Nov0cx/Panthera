#include "UIHelper.hpp"

namespace Panthera::UI
{
    void RenderDropDown(const std::string& name, const std::string& currentName, const std::vector<std::string>& names, std::function<void(int)> callback, ImGuiComboFlags flags)
    {
        if (ImGui::BeginCombo(name.c_str(), currentName.c_str(), flags))
        {
            for (int i = 0; i < names.size(); i++)
            {
                bool is_selected = (i == 0);
                if (ImGui::Selectable(names[i].c_str(), is_selected))
                {
                    callback(i);
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
    }

    void ClampedDragFloat3(const std::string& name, glm::vec3& value, float min, float max, float step)
    {
        ImGui::DragFloat3(name.c_str(), &value.x, step, min, max);
    }

    void ClampedDragFloat2(const std::string &name, glm::vec2 &value, float min, float max, float step)
    {
        ImGui::DragFloat2(name.c_str(), &value.x, step, min, max);
    }

    void ClampedDragFloat(const std::string &name, float &value, float min, float max, float step)
    {
        ImGui::DragFloat(name.c_str(), &value, step, min, max);
    }

    template<typename T>
    void DragAndDropSource(std::string &name, std::function<void(const ImGuiPayload *)> handle)
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(name.c_str()))
            {
                handle(payload);
            }
            ImGui::EndDragDropTarget();
        }
    }
}