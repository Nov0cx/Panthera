#ifndef PANTHERA_ORTHOGRAPHICCAMERA_HPP
#define PANTHERA_ORTHOGRAPHICCAMERA_HPP

#include "ppch.hpp"

namespace Panthera
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera();
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& position);
        void SetRotation(float rotation);

        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline float GetRotation() const { return m_Rotation; }

        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        float m_Rotation = 0.0f;
    };
}


#endif //PANTHERA_ORTHOGRAPHICCAMERA_HPP
