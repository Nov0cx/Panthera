#include "OrthographicCameraController.hpp"

#include "Panthera/Core/Input.hpp"
#include "Panthera/Events/MouseEvents.hpp"
#include "Panthera/Events/WindowEvents.hpp"

namespace Panthera
{

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoom)
        : m_AspectRatio(aspectRatio), m_Zoom(zoom)
    {
        m_Camera = OrthographicCamera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
    }

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, const glm::vec3 &pos, float rotation,
                                                               float zoom)
            : m_AspectRatio(aspectRatio), m_Zoom(zoom)
    {
        m_Camera = OrthographicCamera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
        m_Camera.SetPosition(pos);
        m_Camera.SetRotation(rotation);
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(Key::A))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f) * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::D))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f) * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::W))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f) * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::S))
        {
            m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.0f, -1.0f, 0.0f) * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::Q))
        {
            m_Camera.SetRotation(m_Camera.GetRotation() - glm::radians(20.0f) * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::E))
        {
            m_Camera.SetRotation(m_Camera.GetRotation() + glm::radians(20.0f) * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::R))
        {
            SetZoom(m_Zoom + 0.23f * ts.GetSeconds());
        }
        if (Input::IsKeyPressed(Key::F))
        {
            SetZoom(m_Zoom - 0.23f * ts.GetSeconds());
        }
    }

    void OrthographicCameraController::OnEvent(Event &event)
    {
        static Event::Listener<MouseScrollEvent> scrollListener([this](auto &&e){ SetZoom(m_Zoom + e.PosY * 0.1f); });
        scrollListener.Run(event, EventSubType::MouseScrollEvent);
        /*static Event::Listener<WindowResizeEvent> windowResizeEventListener([this] (auto&& e) {
            WindowResizeEvent& windowResizeEvent = dynamic_cast<WindowResizeEvent&>(e);
            Resize(windowResizeEvent.Width, windowResizeEvent.Height);
        });
        windowResizeEventListener.Run(event, EventSubType::WindowResizeEvent);*/
    }

    void OrthographicCameraController::SetZoom(float zoom)
    {
        m_Zoom = zoom;
        m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    }

    void OrthographicCameraController::SetAspectRatio(float aspectRatio)
    {
        m_AspectRatio = aspectRatio;
        m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    }

    OrthographicCamera &OrthographicCameraController::GetCamera()
    {
        return m_Camera;
    }

    float OrthographicCameraController::GetZoom() const
    {
        return m_Zoom;
    }

    float OrthographicCameraController::GetAspectRatio() const
    {
        return m_AspectRatio;
    }

    void OrthographicCameraController::Resize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    }
}