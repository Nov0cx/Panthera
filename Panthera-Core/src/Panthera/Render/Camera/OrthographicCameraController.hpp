#ifndef PANTHERA_ORTHOGRAPHICCAMERACONTROLLER_HPP
#define PANTHERA_ORTHOGRAPHICCAMERACONTROLLER_HPP

#include "OrthographicCamera.hpp"
#include "Panthera/Core/Timestep.hpp"
#include "Panthera/Core/Event.hpp"

namespace Panthera
{

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, float zoom = 1.0f);
        OrthographicCameraController(float aspectRatio, const glm::vec3 &pos, float rotation, float zoom = 1.0f);
        OrthographicCameraController() = default;
        ~OrthographicCameraController() = default;
        void OnUpdate(Timestep ts);
        void OnEvent(Event& event);

        void SetZoom(float zoom);
        void SetAspectRatio(float aspectRatio);

        OrthographicCamera& GetCamera();

        float GetZoom() const;
        float GetAspectRatio() const;

    private:
        OrthographicCamera m_Camera;
        float m_AspectRatio, m_Zoom;
    };

}

#endif //PANTHERA_ORTHOGRAPHICCAMERACONTROLLER_HPP
