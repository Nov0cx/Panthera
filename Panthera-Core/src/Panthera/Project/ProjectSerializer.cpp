#include "ProjectSerializer.hpp"

#include <nlohmann/json.hpp>
#include "Panthera/Scene/SceneSerializer.hpp"
#include "Panthera/Core/Log.hpp"

#include <fstream>

namespace Panthera
{

    void ProjectSerializer::Serialize(const Project *project)
    {
        nlohmann::json json;
        json["name"] = project->GetName();
        json["scenes"] = {};
        json["renderer_api"] = project->GetRendererAPI();
        for (auto scene : project->GetScenes())
        {
            json["scenes"].push_back(SceneSerializer::Serialize(*scene));
        }

        std::ofstream file(project->GetPath());
        if (file.is_open())
        {
            file << json.dump();
            file.close();
        }
        else
        {
            FAIL("Failed to open file: " + project->GetPath());
        }
    }

    Project *ProjectSerializer::Deserialize(const std::string &path)
    {
        return NULL;
    }
}