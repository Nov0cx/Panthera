#ifndef PANTHERA_ENTITY_HPP
#define PANTHERA_ENTITY_HPP

#include <entt/entt.hpp>
#include "Scene.hpp"
#include "Panthera/Core/Log.hpp"
#include "UUID.hpp"
#include <string>

namespace Panthera
{
    class SceneEntity
    {
    public:
        SceneEntity(entt::entity entity, Scene *scene);

        SceneEntity() = default;

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

        template<typename... Components>
        inline bool HasAnyOf()
        {
            return m_Scene->m_Registry.any_of<Components...>(m_Entity);
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
        inline bool HasComponents()
        {
            entt::registry &registry = m_Scene->m_Registry;
            return registry.all_of<Classes...>(m_Entity);
        }

        inline void Destroy()
        {
            m_Scene->DestroyEntity(*this);
        }

        entt::entity GetEntity();
        operator entt::entity();

        inline operator bool()
        {
            return m_Entity != entt::null && m_Scene != nullptr;
        }

        inline bool operator ==(const SceneEntity &other)
        {
            return m_Entity == other.m_Entity && m_Scene == other.m_Scene;
        }

        inline bool operator !=(const SceneEntity &other)
        {
            return m_Entity != other.m_Entity || m_Scene != other.m_Scene;
        }

        std::string& GetName();
        UUID GetUUID();
    private:
        entt::entity m_Entity{ entt::null };
        Scene *m_Scene = nullptr;
    };


}

#endif //PANTHERA_ENTITY_HPP
