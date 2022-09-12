#ifndef PANTHERA_WINDOW_HPP
#define PANTHERA_WINDOW_HPP

#include "ppch.hpp"

namespace Panthera
{
    struct WindowInfo
    {
        String Title = "Panthera Window";
        uint32_t Width = 0, Height = 0;
        bool VSync = false;
    };

    class Window
    {
    public:
        Ref<Window> Create(const WindowInfo &info);
    public:
        virtual void Update() = 0;

        virtual void* GetNativeWindow() = 0;

        virtual WindowInfo& GetInfo() = 0;
        virtual const WindowInfo& GetInfo() const = 0;
    private:
    };
}

#endif //PANTHERA_WINDOW_HPP
