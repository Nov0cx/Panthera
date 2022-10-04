#ifndef PANTHERA_UIINTERNAL_HPP
#define PANTHERA_UIINTERNAL_HPP

#include "ppch.hpp"
#include <tsl/sparse_map.h>
#include "Panthera/Renderer/Window/Window.hpp"

namespace Panthera::UI::Internal
{
    struct Data
    {
        static Data Instance;

        tsl::sparse_map<const char*, Ref<Window>> Windows = {};
        bool Locked = true;
    };

}

#endif //PANTHERA_UIINTERNAL_HPP
