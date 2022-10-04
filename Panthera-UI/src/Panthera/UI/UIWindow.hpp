#ifndef PANTHERA_UIWINDOW_HPP
#define PANTHERA_UIWINDOW_HPP

#include "ppch.hpp"

namespace Panthera::UI
{
    void BeginIteration();
    void EndIteration();

    bool BeginContext(const String& name);
    void EndContext();
}

#endif //PANTHERA_UIWINDOW_HPP
