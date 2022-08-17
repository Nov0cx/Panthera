#include "SceneSerializer.hpp"

#include <nlohmann/json.hpp>
#include "Entity.hpp"
#include "Components.hpp"
#include <string>

using json = nlohmann::json;

namespace Panthera
{

    static json SerializeEntity(Scene &scene, SceneEntity entity)
    {
        json entityJson;

        NameComponent name = entity.GetComponent<NameComponent>();

        std::string entityID = std::to_string(entity.GetUUID());
        entityJson[entityID] = {
                {"uuid", entity.GetUUID().Get()},
        };

        entityJson[entityID]["components"]["name"] = name.Name;

        if (entity.HasComponent<TransformComponent>())
        {
            TransformComponent transform = entity.GetComponent<TransformComponent>();
            entityJson[entityID]["components"]["transform"] = {
                    {"position", {
                            {"x", transform.Translation.x},
                            {"y", transform.Translation.y},
                            {"z", transform.Translation.z}
                    }},
                    {"rotation", {
                            {"x", transform.Rotation.x},
                            {"y", transform.Rotation.y},
                            {"z", transform.Rotation.z}
                    }},
                    {"scale", {
                            {"x", transform.Scale.x},
                            {"y", transform.Scale.y},
                            {"z", transform.Scale.z}
                    }}
            };
        }

        if (entity.HasComponent<QuadComponent>())
        {
            QuadComponent quad = entity.GetComponent<QuadComponent>();
            entityJson[entityID]["components"]["quad"] = {
                    {"color", {
                            {"r", quad.Color.r},
                            {"g", quad.Color.g},
                            {"b", quad.Color.b},
                            {"a", quad.Color.a}
                    }},
                    {"tiling", quad.Tiling},
                    {"texture", quad.Texture ? quad.Texture->GetPath() : ""}
            };
        }

        if (entity.HasComponent<CircleComponent>())
        {
            CircleComponent circle = entity.GetComponent<CircleComponent>();
            entityJson[entityID]["components"]["circle"] = {
                    {"color", {
                            {"r", circle.Color.r},
                            {"g", circle.Color.g},
                            {"b", circle.Color.b},
                            {"a", circle.Color.a}
                    }},
                    {"borderThickness", circle.BorderThickness},
                    {"fade", circle.Fade},
                    {"tiling", circle.Tiling},
                    {"texture", circle.Texture ? circle.Texture->GetPath() : ""}
            };
        }

        return entityJson;
    }

    void SceneSerializer::Serialize(Scene &scene, std::string filename)
    {

    }

    Scene *SceneSerializer::Deserialize(std::string filename)
    {
        return NULL;
    }
}