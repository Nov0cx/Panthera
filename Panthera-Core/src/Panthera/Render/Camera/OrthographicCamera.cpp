#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Panthera
{

    Panthera::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
          m_ViewMatrix(1.0f)
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    Panthera::OrthographicCamera::~OrthographicCamera()
    {}

    void Panthera::OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Panthera::OrthographicCamera::SetPosition(const glm::vec3 &position)
    {
        m_Position = position;
        Recalculate();
    }

    void Panthera::OrthographicCamera::SetRotation(float rotation)
    {
        m_Rotation = rotation;
        Recalculate();
    }

    const glm::vec3 &Panthera::OrthographicCamera::GetPosition() const
    {
        return m_Position;
    }

    float Panthera::OrthographicCamera::GetRotation() const
    {
        return m_Rotation;
    }

    const glm::mat4 &Panthera::OrthographicCamera::GetProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    const glm::mat4 &Panthera::OrthographicCamera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    const glm::mat4 &Panthera::OrthographicCamera::GetViewProjectionMatrix() const
    {
        return m_ViewProjectionMatrix;
    }

    void Panthera::OrthographicCamera::Recalculate()
    {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * rotationMatrix;

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}