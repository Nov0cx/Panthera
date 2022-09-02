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
}