#ifndef PANTHERA_SCENESERIALIZER_HPP
#define PANTHERA_SCENESERIALIZER_HPP

#include "Scene.hpp"
#include <nlohmann/json.hpp>

namespace Panthera
{
    class SceneSerializer
    {
    public:
        static void Serialize(Scene& scene, const std::string &filename);
        static nlohmann::json Serialize(Scene& scene);
        static Scene* Deserialize(const std::string& filename);
    private:
    };
}

#endif //PANTHERA_SCENESERIALIZER_HPP
