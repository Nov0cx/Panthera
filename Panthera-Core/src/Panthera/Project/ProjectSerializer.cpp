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

        std::ofstream file(project->GetPath(), std::ios::binary);
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
        std::ifstream file(path, std::ios::binary);
        if (file.is_open())
        {
            nlohmann::json json;
            file >> json;
            file.close();
            Project *project = new Project(json["name"], path, json["renderer_api"]);
            for (auto scene : json["scenes"])
            {
                project->AddScene(SceneSerializer::Deserialize(scene));
            }
            return project;
        }
        else
        {
            file.close();
            FAIL("Failed to open file: " + path);
        }
        return nullptr;
    }
}