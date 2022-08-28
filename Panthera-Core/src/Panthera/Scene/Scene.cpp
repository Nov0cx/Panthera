#include "Scene.hpp"

#include "Entity.hpp"
#include "Components.hpp"
#include "SceneSerializer.hpp"
#include "Panthera/Core/Log.hpp"
#include <glm/gtx/string_cast.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include "Panthera/Core/Event.hpp"
#include "Panthera/Events/WindowEvents.hpp"
#include "Panthera/Core/Application.hpp"

#include <utility>

namespace Panthera
{

    Scene::Scene(OrthographicCameraController camera, const std::string &name, const std::string &path)
            : m_Renderer(Renderer::Create()), m_Name(std::move(name)), m_Camera(camera), m_Path(std::move(path))
    {
        m_Renderer->Init();
    }

    Scene::~Scene()
    {

    }

    void Scene::OnUpdate(Timestep ts)
    {
        if (((m_ViewportSize.x > 0 || m_ViewportSize.y > 0) &&
             (m_ViewportSize.x != m_LastViewportSize.x || m_ViewportSize.y != m_LastViewportSize.y)) ||
            !m_HasBeginResized)
        {
            m_Renderer->GetFramebuffer()->ResizeAttachments(m_LastViewportSize.x, m_LastViewportSize.y);
            m_Renderer->GetFramebuffer()->SetViewport(0, 0, m_LastViewportSize.x, m_LastViewportSize.y);
            m_Camera.Resize(m_LastViewportSize.x, m_LastViewportSize.y);

            m_ViewportSize = m_LastViewportSize;
            m_HasBeginResized = true;
        }

        m_Camera.OnUpdate(ts);
        m_Renderer->Clear();
        m_Renderer->BeginScene(m_Camera.GetCamera());

        auto quadView = m_Registry.view<TransformComponent, QuadComponent>();
        for (auto entity: quadView)
        {
            auto[transform, quad] = quadView.get<TransformComponent, QuadComponent>(entity);
            glm::mat4 quadTransform = transform.GetTransform();
            if (quad.Texture)
            {
                m_Renderer->DrawQuad(quadTransform, quad.Color, quad.Tiling, quad.Texture);
            } else
            {
                m_Renderer->DrawQuad(quadTransform, quad.Color);
            }
        }

        auto circleView = m_Registry.view<TransformComponent, CircleComponent>();
        for (auto entity: circleView)
        {
            auto[transform, circle] = circleView.get<TransformComponent, CircleComponent>(entity);
            glm::mat4 circleTransform = transform.GetTransform();
            if (circle.Texture)
            {
                m_Renderer->DrawCircle(circleTransform, circle.Color, circle.BorderThickness, circle.Fade,
                                       circle.Tiling, circle.Texture);
            } else
            {
                m_Renderer->DrawCircle(circleTransform, circle.Color, circle.BorderThickness, circle.Fade);
            }
        }

        auto triangleView = m_Registry.view<TransformComponent, TriangleComponent>();
        for (auto entity: triangleView)
        {
            auto[transform, triangle] = triangleView.get<TransformComponent, TriangleComponent>(entity);
            glm::mat4 triangleTransform = transform.GetTransform();
            if (triangle.Texture)
            {
                m_Renderer->DrawTriangle(triangleTransform, triangle.Color, triangle.Tiling, triangle.Texture);
            } else
            {
                m_Renderer->DrawTriangle(triangleTransform, triangle.Color);
            }
        }

        auto lineView = m_Registry.view<LineTransformComponent, LineComponent>(entt::exclude < TransformComponent > );
        for (auto entity: lineView)
        {
            auto[transform, line] = lineView.get<LineTransformComponent, LineComponent>(entity);
            m_Renderer->DrawLine(transform.Start, transform.End, line.Color, line.Thickness);
        }

        m_Renderer->EndScene();
    }

    void Scene::OnEvent(Event &e)
    {
        /*static Event::Listener<WindowResizeEvent> windowResizeEventListener([this] (auto&& e) {
            WindowResizeEvent& windowResizeEvent = dynamic_cast<WindowResizeEvent&>(e);
            m_Renderer->GetFramebuffer()->ResizeAttachments(windowResizeEvent.Width, windowResizeEvent.Height);
            m_Renderer->GetFramebuffer()->SetViewport(0, 0, windowResizeEvent.Width, windowResizeEvent.Height);
        });
        windowResizeEventListener.Run(e, EventSubType::WindowResizeEvent);*/
        m_Camera.OnEvent(e);
    }

    SceneEntity Scene::CreateEntity(const char *name)
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

    void Scene::OnImGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Scene Viewport");

        Application::GetInstance()->GetImGuiLayer()->SetBlockEvents(!ImGui::IsWindowFocused() && !ImGui::IsWindowHovered());

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_LastViewportSize = ImVec2{viewportPanelSize.x, viewportPanelSize.y};
        if (m_ViewportSize.x == 0 || m_ViewportSize.y == 0)
            m_ViewportSize = ImVec2{viewportPanelSize.x, viewportPanelSize.y};

        if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0)
        {
            ImGui::Image(reinterpret_cast<void *>(m_Renderer->GetFramebuffer()->GetColorAttachment(
                                 0).Texture->GetRendererID()),
                         ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    Renderer *Scene::GetRenderer()
    {
        return m_Renderer;
    }

    void Scene::ForAllEntities(std::function<void(SceneEntity &)> func)
    {
        for (auto entity: m_Registry.view<NameComponent, IDComponent>())
        {
            SceneEntity sceneEntity(entity, this);
            func(sceneEntity);
        }
    }
}