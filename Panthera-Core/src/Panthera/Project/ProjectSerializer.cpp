#include "ProjectSerializer.hpp"

#include <nlohmann/json.hpp>
#include "Panthera/Scene/SceneSerializer.hpp"
#include "Panthera/Core/Log.hpp"

#include <fstream>

namespace Panthera
{

    void ProjectSerializer::Serialize(Ref<Project> project)
    {
        nlohmann::json json;
        json["name"] = project->GetName();
        json["scenes"] = {};
        json["renderer_api"] = project->GetRendererAPI();
        json["active_scene"] = project->GetActiveScene()->GetName();
        for (auto scene : project->GetScenes())
        {
            if (scene->GetPath() != "")
                json["scenes"].push_back(scene->GetPath());
        }

        std::ofstream file(project->GetPath(), std::ios::binary);
        if (file.is_open())
        {
            file << json.dump(4);
            file.close();
        }
        else
        {
            FAIL("Failed to open file: " + project->GetPath());
        }
    }

    Ref<Project> ProjectSerializer::Deserialize(const std::string &path)
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
                if (scene.get<std::string>() != "")
                    project->AddScene(SceneSerializer::Deserialize(scene));
            }
            project->SetActiveScene(json["active_scene"].get<std::string>());
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