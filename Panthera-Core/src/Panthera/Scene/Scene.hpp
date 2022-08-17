#ifndef PANTHERA_SCENE_HPP
#define PANTHERA_SCENE_HPP

#include <entt/entt.hpp>
#include "Panthera/Core/Timestep.hpp"
#include "Panthera/Core/Event.hpp"
#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Render/Camera/OrthographicCamera.hpp"
#include "UUID.hpp"



namespace Panthera
{
    // fwd
    class SceneEntity;
    class SceneSerializer;

    class Scene
    {
    public:
        Scene(OrthographicCamera* camera);
        ~Scene();

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        SceneEntity CreateEntity(const char* name);
        SceneEntity CreateEntity(UUID uuid, const char* name);

    private:
        entt::registry m_Registry;
        Renderer* m_Renderer;
        OrthographicCamera* m_Camera;

        friend class SceneEntity;
        friend class SceneSerializer;
    };
}

#endif //PANTHERA_SCENE_HPP
