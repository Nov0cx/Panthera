#include "Window.hpp"

#ifdef PANTHERA_PLATFORM_WINDOWS
#include "Panthera/Platform/Windows/WindowsWindow.hpp"
#endif

namespace Panthera
{
    Ref <Window> Window::Create(const WindowInfo &info)
    {
#ifdef PANTHERA_PLATFORM_WINDOWS
        return Ref<WindowsWindow>::Create(info);
#else
        return nullptr;
#endif
    }
}