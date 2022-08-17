#include "Scene.hpp"

#include "Entity.hpp"
#include "Components.hpp"
#include "SceneSerializer.hpp"

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

        auto circleGroup = m_Registry.group<TransformComponent>(entt::get<CircleComponent>);
        for (auto entity : circleGroup)
        {
            auto transform = circleGroup.get<TransformComponent>(entity);
            auto circle = circleGroup.get<CircleComponent>(entity);
            glm::mat4 circleTransform = transform.GetTransform();
            if (circle.Texture)
            {
                m_Renderer->DrawCircle(circleTransform, circle.Color, circle.BorderThickness, circle.Fade, circle.Tiling, circle.Texture);
            }
            else
            {
                m_Renderer->DrawCircle(circleTransform, circle.Color, circle.BorderThickness, circle.Fade);
            }
        }

        auto triangleGroup = m_Registry.group<TransformComponent>(entt::get<TriangleComponent>);
        for (auto entity : triangleGroup)
        {
            auto transform = triangleGroup.get<TransformComponent>(entity);
            auto triangle = triangleGroup.get<TriangleComponent>(entity);
            glm::mat4 triangleTransform = transform.GetTransform();
            if (triangle.Texture)
            {
                m_Renderer->DrawTriangle(triangleTransform, triangle.Color, triangle.Tiling, triangle.Texture);
            }
            else
            {
                m_Renderer->DrawTriangle(triangleTransform, triangle.Color);
            }
        }

        auto lineGroup = m_Registry.group<LineTransformComponent>(entt::get<LineComponent>);
        for (auto entity : lineGroup)
        {
            auto transform = lineGroup.get<LineTransformComponent>(entity);
            auto line = lineGroup.get<LineComponent>(entity);
            m_Renderer->DrawLine(transform.Start, transform.End, line.Color, line.Thickness);
        }

        m_Renderer->EndScene();
    }

    void Scene::OnEvent(Event &e)
    {
    }

    SceneEntity Scene::CreateEntity(const char* name)
    {
        SceneEntity entity(m_Registry.create(), this);
        entity.CreateComponent<IDComponent>(UUID::UUID());
        entity.CreateComponent<NameComponent>(name);
        return entity;
    }
}