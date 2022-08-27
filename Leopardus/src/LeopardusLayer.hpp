#ifndef PANTHERA_LEOPARDUSLAYER_HPP
#define PANTHERA_LEOPARDUSLAYER_HPP

#include "Panthera/Panthera.hpp"
#include "SceneHierarchyPanel.hpp"

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
        void RenderMenu();
        void SaveProject();
    private:
        Project* m_Project;
        bool loadedScene = false;
        SceneHierarchyPanel *m_SceneHierarchyPanel;
    };
}

#endif //PANTHERA_LEOPARDUSLAYER_HPP
