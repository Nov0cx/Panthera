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

        std::filesystem::path p = std::filesystem::path(m_Path).parent_path().string() + "/scenes";
        if (!std::filesystem::exists(p))
        {
            std::filesystem::create_directory(p);
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