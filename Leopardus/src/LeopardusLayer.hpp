#ifndef PANTHERA_LEOPARDUSLAYER_HPP
#define PANTHERA_LEOPARDUSLAYER_HPP

#include "Panthera/Panthera.hpp"

namespace Panthera
{
    class Leoparuds : public Layer
    {
    public:
        Leoparuds() : Layer();

        virtual void OnStart() override;

        virtual void OnEnd() override;

        virtual void OnUpdate(Panthera::Timestep ts) override;

        virtual void OnEvent(Panthera::Event &e) override;

    private:
        Panthera::Ref <Panthera::Texture2D> m_ColorTexture, m_FlowerTexture, m_FormTexture;
        Panthera::OrthographicCameraController m_CameraController;
        Panthera::Scene *m_Scene;
        bool loadedScene = false;
    };
}

#endif //PANTHERA_LEOPARDUSLAYER_HPP
