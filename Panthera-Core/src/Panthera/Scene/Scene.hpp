#ifndef PANTHERA_SCENE_HPP
#define PANTHERA_SCENE_HPP

#include <entt/entt.hpp>
#include "Panthera/Core/Timestep.hpp"
#include "Panthera/Core/Event.hpp"
#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Render/Camera/OrthographicCamera.hpp"

namespace Panthera
{
    class SceneEntity;

    class Scene
    {
    public:
        Scene(OrthographicCamera& camera);
        ~Scene();

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        SceneEntity CreateEntity(const char* name);

    private:
        entt::registry m_Registry;
        friend class Entity;
        Renderer* m_Renderer;
        OrthographicCamera m_Camera;
    };
}

#endif //PANTHERA_SCENE_HPP
