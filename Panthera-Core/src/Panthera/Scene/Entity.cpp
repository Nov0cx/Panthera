#include "Entity.hpp"

#include "Scene.hpp"

namespace Panthera
{

    SceneEntity::SceneEntity(entt::entity entity, Scene* scene, UUID uuid)
    {
        m_Entity = entity;
        m_Scene = scene;
        m_UUID = uuid;
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
        return m_UUID;
    }
}