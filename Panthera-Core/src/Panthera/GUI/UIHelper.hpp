#ifndef PANTHERA_UIHELPER_HPP
#define PANTHERA_UIHELPER_HPP

#include <vector>
#include <imgui.h>
#include <string>
#include <functional>
#include <glm/glm.hpp>

namespace Panthera::UI
{
    template<typename T>
    inline T RenderEnumDropDown(const std::string& name, T current, const char** names, size_t length, ImGuiComboFlags flags = ImGuiComboFlags_None)
    {
        static_assert(std::is_enum<T>::value, "T must be an enum");

        if (ImGui::BeginCombo(name.c_str(), names[(int)current], flags))
        {
            for (int i = 0; i < length; i++)
            {
                bool is_selected = ((int)current == i);
                if (ImGui::Selectable(names[i], is_selected))
                {
                    current = static_cast<T>(i);
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        return current;
    }

    template<typename T>
    inline T RenderDropDown(const std::string& name, const std::string& currentName, const std::vector<std::string>& names, T current, const std::vector<T> &options, ImGuiComboFlags flags = ImGuiComboFlags_None)
    {
        if (ImGui::BeginCombo(name.c_str(), currentName.c_str(), flags))
        {
            for (int i = 0; i < names.size(); i++)
            {
                bool is_selected = (current == options[i]);
                if (ImGui::Selectable(names[i].c_str(), is_selected))
                {
                    current = options[i];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        return current;
    }

    void RenderDropDown(const std::string& name, const std::string& currentName, const std::vector<std::string>& names, std::function<void(int)> callback, ImGuiComboFlags flags = ImGuiComboFlags_None);

    void ClampedDragFloat3(const std::string& name, glm::vec3& value, float min = 0.001f, float max = 1.0f, float step = 0.001f);
    void ClampedDragFloat2(const std::string& name, glm::vec2& value, float min = 0.001f, float max = 1.0f, float step = 0.001f);
    void ClampedDragFloat(const std::string& name, float& value, float min = 0.001f, float max = 1.0f, float step = 0.001f);

    template<typename T>
    void DragAndDropSource(std::string& name, std::function<void(const ImGuiPayload*)> handle);
}

#endif //PANTHERA_UIHELPER_HPP
