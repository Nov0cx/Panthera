#ifndef PANTHERA_LEOPARDUSLAYER_HPP
#define PANTHERA_LEOPARDUSLAYER_HPP

#include "Panthera/Panthera.hpp"

namespace Panthera
{
    class LeoparudsLayer : public Layer
    {
    public:
        LeoparudsLayer();
        ~LeoparudsLayer();

        virtual void OnStart() override;

        virtual void OnEnd() override;

        virtual void OnUpdate(Panthera::Timestep ts) override;

        virtual void OnEvent(Panthera::Event &e) override;

        virtual void OnImGuiRender() override;

    private:
        Ref <Texture2D> m_ColorTexture, m_FlowerTexture, m_FormTexture;
        OrthographicCameraController m_CameraController;
        Scene *m_Scene;
        bool loadedScene = false;
    };
}

#endif //PANTHERA_LEOPARDUSLAYER_HPP
