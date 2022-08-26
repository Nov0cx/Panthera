#ifndef PANTHERA_SCENE_HPP
#define PANTHERA_SCENE_HPP

#include <entt/entt.hpp>
#include "Panthera/Core/Timestep.hpp"
#include "Panthera/Core/Event.hpp"
#include "Panthera/Render/Renderer.hpp"
#include "Panthera/Render/Camera/OrthographicCameraController.hpp"
#include "UUID.hpp"
#include <imgui.h>
#include "Components.hpp"

namespace Panthera
{
    // fwd
    class SceneEntity;
    class SceneSerializer;

    class Scene
    {
    public:
        Scene(OrthographicCameraController camera, const std::string& name = "Scene");
        ~Scene();

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);
        void OnImGuiRender();

        SceneEntity CreateEntity(const char* name);
        SceneEntity CreateEntity(UUID uuid, const char* name);

        Renderer* GetRenderer();

        template<class... Components>
        auto GetEntitiesWith()
        {
            return m_Registry.view<Components...>();
        }

        void ForAllEntities(std::function<void(SceneEntity&)> func);

        inline std::string &GetName() { return m_Name; }
    private:
        entt::registry m_Registry;
        Renderer* m_Renderer;
        OrthographicCameraController m_Camera;
        ImVec2 m_ViewportSize;
        ImVec2 m_LastViewportSize;
        std::string m_Name;

        friend class SceneEntity;
        friend class SceneSerializer;
    };
}

#endif //PANTHERA_SCENE_HPP
