#include "Project.hpp"

#include <utility>

namespace Panthera
{
    Project::Project(const std::string &name, const std::string &path, RendererAPI api)
        : m_Name(std::move(name)), m_Path(std::move(path)), m_RendererAPI(api)
    {}

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