#include "Entity.hpp"

#include "Scene.hpp"

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
}