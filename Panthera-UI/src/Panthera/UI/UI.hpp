#ifndef PANTHERA_UI_HPP
#define PANTHERA_UI_HPP

#include "ppch.hpp"

namespace Panthera::UI
{
    void Init();

    void BeginIteration();
    void EndIteration();

    bool BeginContext(const String& name);
    void EndContext();
}

#endif //PANTHERA_UI_HPP
