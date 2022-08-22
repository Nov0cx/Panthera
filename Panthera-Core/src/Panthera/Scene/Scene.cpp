#include "Scene.hpp"

#include "Entity.hpp"
#include "Components.hpp"
#include "SceneSerializer.hpp"
#include "Panthera/Core/Log.hpp"
#include <glm/gtx/string_cast.hpp>

namespace Panthera
{

    Scene::Scene(OrthographicCamera* camera)
        : m_Renderer(Renderer::Create())
    {
        m_Camera = camera;
        m_Renderer->Init();
    }

    Scene::~Scene()
    {

    }

    void Scene::OnUpdate(Timestep ts)
    {
        m_Renderer->Clear();
        m_Renderer->BeginScene(*m_Camera);

        auto quadView = m_Registry.view<TransformComponent, QuadComponent>();
        for (auto entity : quadView)
        {
            auto[transform, quad] = quadView.get<TransformComponent, QuadComponent>(entity);
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

        auto circleView = m_Registry.view<TransformComponent, CircleComponent>();
        for (auto entity : circleView)
        {
            auto[transform, circle] = circleView.get<TransformComponent, CircleComponent>(entity);
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

        auto triangleView = m_Registry.view<TransformComponent, TriangleComponent>();
        for (auto entity : triangleView)
        {
            auto[transform, triangle] = triangleView.get<TransformComponent, TriangleComponent>(entity);
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

        auto lineView = m_Registry.view<LineTransformComponent, LineComponent>(entt::exclude<TransformComponent>);
        for (auto entity : lineView)
        {
            auto[transform, line] = lineView.get<LineTransformComponent, LineComponent>(entity);
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

    SceneEntity Scene::CreateEntity(Panthera::UUID uuid, const char *name)
    {
        SceneEntity entity(m_Registry.create(), this);
        entity.CreateComponent<IDComponent>(uuid);
        entity.CreateComponent<NameComponent>(name);
        return entity;
    }
}