#include "Entity.hpp"

#include "Scene.hpp"
#include "Components.hpp"

namespace Panthera
{

    SceneEntity::SceneEntity(entt::entity entity, Scene* scene)
    {
        m_Entity = entity;
        m_Scene = scene;
    }

    SceneEntity::~SceneEntity()
    {

    }

    entt::entity SceneEntity::GetEntity()
    {
        return m_Entity;
    }

    SceneEntity::operator entt::entity()
    {
        return m_Entity;
    }

    UUID SceneEntity::GetUUID()
    {
        return GetComponent<IDComponent>().ID;
    }
}