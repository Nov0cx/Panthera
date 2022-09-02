#ifndef PANTHERA_SCENEHIERARCHYPANEL_HPP
#define PANTHERA_SCENEHIERARCHYPANEL_HPP

#include "Panthera/Panthera.hpp"

namespace Panthera
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel();
        ~SceneHierarchyPanel();

        void Render(Ref<Scene> scene);

    private:
        void DrawSelectedEntityProperties(Ref<Scene> scene);
    private:
        SceneEntity m_SelectedEntity;
        bool m_AddComponentPopup = false;
    };
}

#endif //PANTHERA_SCENEHIERARCHYPANEL_HPP
