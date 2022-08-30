#ifndef PANTHERA_LEOPARDUSLAYER_HPP
#define PANTHERA_LEOPARDUSLAYER_HPP

#include "Panthera/Panthera.hpp"
#include "SceneHierarchyPanel.hpp"
#include "ProjectPanel.hpp"

namespace Panthera
{
    class LeoparudsLayer : public Layer
    {
    public:
        LeoparudsLayer();
        ~LeoparudsLayer();

        virtual void OnStart() override;

        virtual void OnEnd() override;

        virtual void OnUpdate(Timestep ts) override;

        virtual void OnEvent(Event &e) override;

        virtual void OnImGuiRender() override;

    private:
        void RenderMenu();
        void CreateProjectMenu();
        void SaveProject();
    private:
        Ref<Project> m_Project = nullptr;
        Ref<SceneHierarchyPanel> m_SceneHierarchyPanel = nullptr;
        Ref<ProjectPanel> m_ProjectPanel = nullptr;
        bool m_ShowCreateProjectWindow = false;
        char m_ProjectName[256] = "";
    };
}

#endif //PANTHERA_LEOPARDUSLAYER_HPP
