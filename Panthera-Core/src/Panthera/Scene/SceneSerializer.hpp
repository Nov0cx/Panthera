#ifndef PANTHERA_SCENESERIALIZER_HPP
#define PANTHERA_SCENESERIALIZER_HPP

#include "Scene.hpp"

namespace Panthera
{
    class SceneSerializer
    {
    public:
        static void Serialize(Scene& scene, const std::string &filename);
        static Scene* Deserialize(const std::string& filename);
    private:
    };
}

#endif //PANTHERA_SCENESERIALIZER_HPP
