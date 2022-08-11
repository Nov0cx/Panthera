#ifndef PANTHERA_ORTHOGRAPHICCAMERA_HPP
#define PANTHERA_ORTHOGRAPHICCAMERA_HPP

#include <glm/glm.hpp>

namespace Panthera
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        OrthographicCamera() = default;
        ~OrthographicCamera();

        void SetProjection(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3 &position);
        // in radians
        void SetRotation(float rotation);

        const glm::vec3 &GetPosition() const;
        // in radians
        float GetRotation() const;

        const glm::mat4 &GetProjectionMatrix() const;
        const glm::mat4 &GetViewMatrix() const;
        const glm::mat4 &GetViewProjectionMatrix() const;
    private:
        void Recalculate();

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        // in radians
        float m_Rotation = 0.0f;
    };
}

#endif //PANTHERA_ORTHOGRAPHICCAMERA_HPP
