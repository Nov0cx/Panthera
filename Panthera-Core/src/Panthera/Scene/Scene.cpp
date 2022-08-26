#include "Scene.hpp"

#include "Entity.hpp"
#include "Components.hpp"
#include "SceneSerializer.hpp"
#include "Panthera/Core/Log.hpp"
#include <glm/gtx/string_cast.hpp>
#include <imgui.h>
#include "Panthera/Core/Event.hpp"
#include "Panthera/Events/WindowEvents.hpp"

namespace Panthera
{

    Scene::Scene(OrthographicCameraController camera)
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
        if ((m_ViewportSize.x > 0 || m_ViewportSize.y > 0) &&
            (m_ViewportSize.x != m_LastViewportSize.x || m_ViewportSize.y != m_LastViewportSize.y))
        {
            m_Renderer->GetFramebuffer()->ResizeAttachments(m_LastViewportSize.x, m_LastViewportSize.y);
            m_Renderer->GetFramebuffer()->SetViewport(0, 0, m_LastViewportSize.x, m_LastViewportSize.y);
            m_Camera.Resize(m_LastViewportSize.x, m_LastViewportSize.y);

            m_ViewportSize = m_LastViewportSize;
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
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        bool open = true;
        ImGui::Begin("Editor DockSpace", &open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("Editor DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
        ImGui::Begin("Scene Viewport");
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
        ImGui::End();
    }

    Renderer *Scene::GetRenderer()
    {
        return m_Renderer;
    }

    void Scene::ForAllEntities(std::function<void(SceneEntity&)> func)
    {
        for (auto entity : m_Registry.view<NameComponent, IDComponent>())
        {
            SceneEntity sceneEntity(entity, this);
            func(sceneEntity);
        }
    }
}