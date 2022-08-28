#ifndef PANTHERA_PROJECTPANEL_HPP
#define PANTHERA_PROJECTPANEL_HPP

#include "Panthera/Panthera.hpp"

namespace Panthera
{
    class ProjectPanel
    {
    public:
        ProjectPanel();
        ~ProjectPanel();

        void Render(Ref<Project>& project);
    };
}

#endif //PANTHERA_PROJECTPANEL_HPP
