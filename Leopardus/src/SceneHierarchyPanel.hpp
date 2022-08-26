#ifndef PANTHERA_SCENEHIERARCHYPANEL_HPP
#define PANTHERA_SCENEHIERARCHYPANEL_HPP

#include "Panthera/Panthera.hpp"

namespace Panthera
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(Scene* scene);
        ~SceneHierarchyPanel();

        void Render();

    private:
        Scene* m_Scene;
    };
}

#endif //PANTHERA_SCENEHIERARCHYPANEL_HPP
