#include "Scene.hpp"

#include "Entity.hpp"
#include "Components.hpp"

namespace Panthera
{

    Scene::Scene(OrthographicCamera& camera)
        : m_Renderer(Renderer::Create())
    {
        m_Camera = camera;
    }

    Scene::~Scene()
    {

    }

    void Scene::OnUpdate(Timestep ts)
    {
        m_Renderer->BeginScene(m_Camera);

        auto quadGroup = m_Registry.group<TransformComponent>(entt::get<QuadComponent>);
        for (auto entity : quadGroup)
        {
            auto transform = quadGroup.get<TransformComponent>(entity);
            auto quad = quadGroup.get<QuadComponent>(entity);
            glm::mat4 quadTransform = transform.GetTransform();
            if (quad.Texture)
            {
                m_Renderer->DrawQuad(quadTransform, quad.Color, quad.Tiling, quad.Texture);
            }
            else
            {
                m_Renderer->DrawQuad(quadTransform, quad.Color);
            }
        }

        m_Renderer->EndScene();
    }

    void Scene::OnEvent(Event &e)
    {

    }

    SceneEntity Scene::CreateEntity()
    {
        return SceneEntity(m_Registry.create(), this);
    }
}