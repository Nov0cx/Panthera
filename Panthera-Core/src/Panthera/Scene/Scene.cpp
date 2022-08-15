#include "Scene.hpp"

#include "Entity.hpp"

namespace Panthera
{

    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::OnUpdate(Timestep ts)
    {

    }

    void Scene::OnEvent(Event &e)
    {

    }

    SceneEntity Scene::CreateEntity()
    {
        return SceneEntity(m_Registry.create(), this);
    }
}