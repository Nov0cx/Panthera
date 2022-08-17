#ifndef PANTHERA_SCENESERIALIZER_HPP
#define PANTHERA_SCENESERIALIZER_HPP

#include "Scene.hpp"

namespace Panthera
{
    class SceneSerializer
    {
    public:
        static void Serialize(Scene& scene, std::string filename);
        static Scene* Deserialize(std::string filename);
    private:
    };
}

#endif //PANTHERA_SCENESERIALIZER_HPP
