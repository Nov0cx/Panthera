#ifndef PANTHERA_SCENE_HPP
#define PANTHERA_SCENE_HPP

#include <entt/entt.hpp>
#include "Panthera/Core/Timestep.hpp"
#include "Panthera/Core/Event.hpp"

namespace Panthera
{
    class SceneEntity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        SceneEntity CreateEntity();

    private:
        entt::registry m_Registry;
        friend class Entity;
    };
}

#endif //PANTHERA_SCENE_HPP
