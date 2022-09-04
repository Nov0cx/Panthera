#include "ScenePanel.hpp"

#include <portable-file-dialogs.h>

namespace Panthera
{
    void ScenePanel::Render(Ref<Scene> scene)
    {
        ImGui::Begin("Scene Properties");

        std::string name = scene->GetName();
        char nameBuffer[256];
        memset(nameBuffer, 0, sizeof(nameBuffer));
        std::strncpy(nameBuffer, name.c_str(), sizeof(nameBuffer));
        if (ImGui::InputText("Current Scene", nameBuffer, sizeof(nameBuffer)))
        {
            if (strlen(nameBuffer) > 0)
                name = std::string(nameBuffer);
        }
        scene->SetName(name);
        ImGui::Separator();

        std::string path = scene->GetPath();
        ImGui::Text("Path: %s", path.c_str());

        ImGui::Separator();

        ImGui::End();
    }
}