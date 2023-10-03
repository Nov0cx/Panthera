#ifndef PANTHERA_UIINTERNAL_HPP
#define PANTHERA_UIINTERNAL_HPP

#include "ppch.hpp"
#include <tsl/sparse_map.h>
#include "Panthera/Renderer/Window/Window.hpp"

namespace Panthera::UI::Internal
{
    struct Data
    {
        static Data *Instance;
        static void Init();

        tsl::sparse_map<const char*, Ref<Window>> Windows = {};
        bool Locked = true;

        void AddWindow(const char* name, Ref<Window> window)
        {
            Windows[name] = window;
        }

        Ref<Window> GetWindow(const char* name)
        {
            return Windows.at(name);
        }
    };

}

#endif //PANTHERA_UIINTERNAL_HPP
