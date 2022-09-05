#include "ProjectPanel.hpp"

#include <portable-file-dialogs.h>

namespace Panthera
{

    ProjectPanel::ProjectPanel()
    {}

    ProjectPanel::~ProjectPanel()
    {}

    static void DragAndDrop(std::function<void(std::string&, std::string&)> callback)
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
            {
                const char* path = (const char*) payload->Data;
                std::string filePath = path;
                std::string extension = Utils::GetFileExtension(filePath);
                callback(filePath, extension);
            }
            ImGui::EndDragDropTarget();
        }
    }

    void ProjectPanel::Render(Ref <Project> &project)
    {
        ImGui::Begin("Project Properties");

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
            auto selection = pfd::select_folder("Select Project Path", path == "" ? Application::GetInstance()->GetCurrentPath() : path).result();
            if (!selection.empty())
            {
                path = selection + "/" + name + ".pproject";
            }
        }
        project->SetPath(path);
        ImGui::Separator();

        const char* items[] = {"None", "OpenGL", "Vulkan", "Direct X", "Metal", "OpenGL ES"};
        project->SetRendererAPI(UI::RenderEnumDropDown<RendererAPI>("Renderer API", project->GetRendererAPI(), items, IM_ARRAYSIZE(items)));

        auto scenes = project->GetScenes();
        std::vector<std::string> sceneNames = {};

        for (auto scene : scenes)
        {
            sceneNames.push_back(scene->GetName());
        }

        UI::RenderDropDown("Active Scene", project->GetActiveScene()->GetName(), sceneNames, [&](int index)
        {
            project->SetActiveScene(scenes[index]);
        });

        DragAndDrop([&](std::string& filePath, std::string& extension)
        {
            if (extension == ".pscene")
            {
                LOG_DEBUG("Dropped scene: {}", filePath);
                project->AddScene(SceneSerializer::Deserialize(filePath));
            }
        });

        if (ImGui::Button("Delete Active Scene"))
        {
            if (project->GetScenes().size() > 1)
            {
                project->RemoveScene(project->GetActiveScene());
                project->SetActiveScene(project->GetScenes()[0]);
            }
            else
            {
                LOG_WARN("Cannot delete the last scene in a project! {} scenes left.", project->GetScenes().size());
            }
        }

        ImGui::Separator();

        ImGui::End();
    }
}