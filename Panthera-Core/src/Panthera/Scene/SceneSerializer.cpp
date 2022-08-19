#include "SceneSerializer.hpp"

#include <nlohmann/json.hpp>
#include "Entity.hpp"
#include "Components.hpp"
#include <string>
#include <entt/entt.hpp>
#include "Panthera/Render/Camera/OrthographicCamera.hpp"
#include <fstream>
#include <glm/glm.hpp>
#include "Panthera/Render/Texture/Texture.hpp"
#include <Panthera/Core/Log.hpp>
#include <Panthera/Core/Application.hpp>

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
                    {"scale",    {
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
                    {"color",   {
                                        {"r",    quad.Color.r},
                                        {"g",     quad.Color.g},
                                        {"b",      quad.Color.b},
                                        {"a", quad.Color.a}
                                }},
                    {"tiling",  quad.Tiling},
                    {"texture", {
                                        {"path", quad.Texture ? quad.Texture->GetPath() : ""},
                                }
                    }
            };
        }

        if (entity.HasComponent<CircleComponent>())
        {
            CircleComponent circle = entity.GetComponent<CircleComponent>();
            entityJson[entityID]["components"]["circle"] = {
                    {"color",           {
                                                {"r",    circle.Color.r},
                                                {"g",     circle.Color.g},
                                                {"b",      circle.Color.b},
                                                {"a", circle.Color.a}
                                        }},
                    {"borderThickness", circle.BorderThickness},
                    {"fade",            circle.Fade},
                    {"tiling",          circle.Tiling},
                    {"texture",         {
                                                {"path", circle.Texture ? circle.Texture->GetPath() : ""},
                                        }
                    }
            };
        }

        if (entity.HasComponent<TriangleComponent>())
        {
            TriangleComponent triangle = entity.GetComponent<TriangleComponent>();
            entityJson[entityID]["components"]["triangle"] = {
                    {"color",   {
                                        {"r",    triangle.Color.r},
                                        {"g",     triangle.Color.g},
                                        {"b",      triangle.Color.b},
                                        {"a", triangle.Color.a}
                                }},
                    {"tiling",  triangle.Tiling},
                    {"texture", {
                                        {"path", triangle.Texture ? triangle.Texture->GetPath() : ""},
                                }
                    }
            };
        }

        if (entity.HasComponent<LineTransformComponent>())
        {
            LineTransformComponent lineTransform = entity.GetComponent<LineTransformComponent>();
            entityJson[entityID]["components"]["lineTransform"] = {
                    {"start", {
                                      {"x", lineTransform.Start.x},
                                      {"y", lineTransform.Start.y},
                                      {"z", lineTransform.Start.z}
                              }},
                    {"end",   {
                                      {"x", lineTransform.End.x},
                                      {"y", lineTransform.End.y},
                                      {"z", lineTransform.End.z}
                              }},
            };
        }

        if (entity.HasComponent<LineComponent>())
        {
            LineComponent line = entity.GetComponent<LineComponent>();
            entityJson[entityID]["components"]["line"] = {
                    {"color",     {
                                          {"r", line.Color.r},
                                          {"g", line.Color.g},
                                          {"b", line.Color.b},
                                          {"a", line.Color.a}
                                  }},
                    {"thickness", line.Thickness},
            };
        }

        return entityJson;
    }

    void SceneSerializer::Serialize(Scene &scene, const std::string &filename)
    {
        json sceneJson;
        sceneJson["camera"] = {
                {"position", {
                                     {"x",   scene.m_Camera->GetPosition().x},
                                     {"y", scene.m_Camera->GetPosition().y},
                                     {"z", scene.m_Camera->GetPosition().z}
                             }},
                {"rotation", {
                                     {"rot", scene.m_Camera->GetRotation()},

                             }}
        };
        sceneJson["entities"] = {};
        scene.m_Registry.each([&](entt::entity entity)
                              {
                                  sceneJson["entities"].push_back(
                                          SerializeEntity(scene, SceneEntity(entity, &scene)));
                              });
        std::ofstream o(filename);
        if (o.is_open())
        {
            o << sceneJson.dump(4);
            o.close();
        }
        else
        {
            LOG_ERROR("Could not open file: " + filename);
        }
    }

    static void DeserializeEntity(Scene &scene, json entity)
    {
        entity = entity[entity.begin().key()];
        SceneEntity sceneEntity = scene.CreateEntity(entity["uuid"].get<uint64_t>(),
                                                     entity["components"]["name"].get<std::string>().c_str());
        if (entity["components"].find("transform") != entity["components"].end())
        {
            sceneEntity.CreateComponent<TransformComponent>(
                    glm::vec3(entity["components"]["transform"]["position"]["x"], entity["components"]["transform"]["position"]["y"],
                              entity["components"]["transform"]["position"]["z"]),
                    glm::vec3(entity["components"]["transform"]["rotation"]["x"], entity["components"]["transform"]["rotation"]["y"],
                              entity["components"]["transform"]["rotation"]["z"]),
                    glm::vec3(entity["components"]["transform"]["scale"]["x"], entity["components"]["transform"]["scale"]["y"],
                              entity["components"]["transform"]["scale"]["z"]));
        }

        if (entity["components"].find("quad") != entity["components"].end())
        {
            sceneEntity.CreateComponent<QuadComponent>(
                    glm::vec4(entity["components"]["quad"]["color"]["r"],
                              entity["components"]["quad"]["color"]["g"],
                              entity["components"]["quad"]["color"]["b"],
                              entity["components"]["quad"]["color"]["a"]),
                    entity["components"]["quad"]["tiling"],
                    entity["components"]["quad"]["texture"]["path"].get<std::string>() != "" ? Texture2D::Create(
                            Texture2DSpecification{
                                    .Path = Application::GetInstance()->GetAssetPath(entity["components"]["quad"]["texture"]["path"].get<std::string>().c_str()).c_str(),
                            })
                                                                                               : nullptr);
        }

        if (entity["components"].find("circle") != entity["components"].end())
        {
            sceneEntity.CreateComponent<CircleComponent>(
                    glm::vec4(entity["components"]["circle"]["color"]["r"],
                              entity["components"]["circle"]["color"]["g"],
                              entity["components"]["circle"]["color"]["b"],
                              entity["components"]["circle"]["color"]["a"]),
                    entity["components"]["circle"]["borderThickness"],
                    entity["components"]["circle"]["fade"],
                    entity["components"]["circle"]["tiling"],
                    entity["components"]["circle"]["texture"]["path"].get<std::string>() != "" ? Texture2D::Create(
                            Texture2DSpecification{
                                    .Path = Application::GetInstance()->GetAssetPath(entity["components"]["circle"]["texture"]["path"].get<std::string>().c_str()).c_str(),
                            })
                                                                                               : nullptr);
        }

        if (entity["components"].find("triangle") != entity["components"].end())
        {
            sceneEntity.CreateComponent<TriangleComponent>(
                    glm::vec4(entity["components"]["triangle"]["color"]["r"],
                              entity["components"]["triangle"]["color"]["g"],
                              entity["components"]["triangle"]["color"]["b"],
                              entity["components"]["triangle"]["color"]["a"]),
                    entity["components"]["triangle"]["tiling"],
                    entity["components"]["triangle"]["texture"]["path"].get<std::string>() != "" ? Texture2D::Create(
                            Texture2DSpecification{
                                    .Path = Application::GetInstance()->GetAssetPath(entity["components"]["triangle"]["texture"]["path"].get<std::string>().c_str()).c_str(),
                            })
                                                                                               : nullptr);
        }

        if (entity["components"].find("lineTransform") != entity["components"].end())
        {
            sceneEntity.CreateComponent<LineTransformComponent>(
                    glm::vec3(entity["components"]["lineTransform"]["start"]["x"],
                              entity["components"]["lineTransform"]["start"]["y"],
                              entity["components"]["lineTransform"]["start"]["z"]),
                    glm::vec3(entity["components"]["lineTransform"]["end"]["x"],
                              entity["components"]["lineTransform"]["end"]["y"],
                              entity["components"]["lineTransform"]["end"]["z"]));
        }

        if (entity["components"].find("line") != entity["components"].end())
        {
            sceneEntity.CreateComponent<LineComponent>(
                    glm::vec4(entity["components"]["line"]["color"]["r"],
                              entity["components"]["line"]["color"]["g"],
                              entity["components"]["line"]["color"]["b"],
                              entity["components"]["line"]["color"]["a"]),
                    entity["components"]["line"]["thickness"]);
        }


    }

    Scene *SceneSerializer::Deserialize(const std::string& filename)
    {
        OrthographicCamera *camera = new OrthographicCamera();
        Scene *scene = new Scene(camera);

        std::ifstream file(filename);
        ASSERT(file.is_open(), "Could not open file: " + filename);
        json sceneJson = json::parse(file);
        file.close();
        camera->SetPosition(glm::vec3(sceneJson["camera"]["position"]["x"], sceneJson["camera"]["position"]["y"],
                                      sceneJson["camera"]["position"]["z"]));
        camera->SetRotation(sceneJson["camera"]["rotation"]["rot"]);

        for (json entity : sceneJson["entities"])
        {
            DeserializeEntity(*scene, entity);
        }

        return scene;
    }
}