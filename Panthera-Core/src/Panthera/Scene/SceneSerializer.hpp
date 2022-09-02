#ifndef PANTHERA_SCENESERIALIZER_HPP
#define PANTHERA_SCENESERIALIZER_HPP

#include "Scene.hpp"
#include "Panthera/Core/Pointer.hpp"
#include <nlohmann/json.hpp>

namespace Panthera
{
    class SceneSerializer
    {
    public:
        static void Serialize(Ref<Scene> scene, const std::string &filename);
        static nlohmann::json Serialize(Ref<Scene> scene);
        static Ref<Scene> Deserialize(const std::string& filename);
        static Ref<Scene> DeserializeJson(const nlohmann::json& json);
    private:
    };
}

#endif //PANTHERA_SCENESERIALIZER_HPP
