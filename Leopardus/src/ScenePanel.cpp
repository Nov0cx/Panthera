#include "ScenePanel.hpp"

#include <portable-file-dialogs.h>

namespace Panthera
{

    void ScenePanel::Render(Scene *scene)
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
        if (ImGui::Selectable(("Path: " + path).c_str()))
        {
            auto selection = pfd::select_folder("Select Scene Path", path == "" ? Application::GetInstance()->GetCurrentPath() : path).result();
            if (!selection.empty())
            {
                path = selection + "/" + name + ".pscene";
            }
        }
        scene->SetPath(path);
        ImGui::Separator();

        ImGui::End();
    }
}