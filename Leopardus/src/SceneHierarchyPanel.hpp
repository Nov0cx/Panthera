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

        void Render(Scene* scene);
    };
}

#endif //PANTHERA_SCENEHIERARCHYPANEL_HPP
