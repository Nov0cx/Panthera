#ifndef PANTHERA_ENTITY_HPP
#define PANTHERA_ENTITY_HPP

#include <entt/entt.hpp>
#include "Scene.hpp"
#include "Panthera/Core/Log.hpp"
#include "UUID.hpp"

namespace Panthera
{
    class SceneEntity
    {
    public:
        SceneEntity(entt::entity entity, Scene *scene);

        ~SceneEntity();

        template<typename T, typename... Args>
        inline T &CreateComponent(Args &&... args)
        {
            ASSERT(!HasComponent<T>(), "Entity already has component of type {}", typeid(T).name());
            return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
        }

        template<typename T>
        inline T &GetComponent()
        {
            ASSERT(HasComponent<T>(), "Entity does not have component of type {}", typeid(T).name());
            return m_Scene->m_Registry.get<T>(m_Entity);
        }

        template<typename T>
        inline bool RemoveComponent()
        {
            if (HasComponent<T>())
            {
                m_Scene->m_Registry.remove<T>(m_Entity);
                return true;
            }
            return false;
        }

        template<typename T>
        inline bool HasComponent()
        {
            return m_Scene->m_Registry.all_of<T>(m_Entity);
        }

        template<typename T, typename... Args>
        inline void CreateOrReplaceComponent(Args &&... args)
        {
            if (HasComponent<T>())
            {
                m_Scene->m_Registry.replace<T>(m_Entity, std::forward<Args>(args)...);
            }
            else
            {
                CreateComponent<T>(std::forward<Args>(args)...);
            }
        }

        template<typename... Classes>
        bool HasComponents()
        {
            entt::registry &registry = m_Scene->m_Registry;
            return registry.all_of<Classes...>(m_Entity);
        }

        entt::entity GetEntity();
        operator entt::entity();

        UUID GetUUID();
    private:
        entt::entity m_Entity;
        Scene *m_Scene;
    };


}

#endif //PANTHERA_ENTITY_HPP
