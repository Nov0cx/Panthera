#ifndef PANTHERA_WINDOW_HPP
#define PANTHERA_WINDOW_HPP

#include <any>
#include <cinttypes>
#include "Panthera/Core/Event.hpp"
#include "Panthera/Core/Pointer.hpp"

namespace Panthera
{
    struct WindowProps
    {
        const char* Title;
        uint32_t Width = 800, Height = 600;
        bool VSync = false;
    };

    class Window
    {
    public:
        static Ref<Window> Create(const WindowProps& props);

        virtual ~Window() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& event) = 0;
        virtual std::any GetNativeWindow() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetVSync(bool state) = 0;
        virtual bool IsVSync() const = 0;

    protected:
        uint16_t p_WindowCount = 0;
    };
}

#endif //PANTHERA_WINDOW_HPP
