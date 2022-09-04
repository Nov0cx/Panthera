#include "Project.hpp"

#include <utility>
#include <filesystem>
#include "Panthera/Core/Application.hpp"

namespace Panthera
{
    Project::Project(const std::string &name, const std::string &path, RendererAPI api)
        : m_Name(std::move(name)), m_Path(std::move(path)), m_RendererAPI(api)
    {
        if (path != "")
        {
            std::filesystem::current_path(std::filesystem::path(m_Path).parent_path());
            LOG_DEBUG("Current path: " + std::filesystem::current_path().string());
            LOG_DEBUG("{}", Application::GetInstance()->GetAssetPath("Panthera/Assets/Gui/imgui.ini"));
        }

        std::filesystem::path assetsPath = std::filesystem::path(m_Path).parent_path().string() + "/Assets";
        if (!std::filesystem::exists(assetsPath))
        {
            std::filesystem::create_directories(assetsPath);
        }

        std::filesystem::path scenesPath = std::filesystem::path(m_Path).parent_path().string() + "/Assets/scenes";
        if (!std::filesystem::exists(scenesPath))
        {
            std::filesystem::create_directories(scenesPath);
        }
    }

    Project::~Project()
    {

    }

    void Project::SetActiveScene(const std::string &name)
    {
        for (auto scene : m_Scenes)
        {
            if (scene->GetName() == name)
            {
                m_ActiveScene = scene;
                return;
            }
        }
    }
}