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
        WindowProps(const char *title, const uint32_t &width = 800, const uint32_t &height = 600, bool vSync = false);

        const char* Title;
        uint32_t Width, Height;
        bool VSync;

    };

    class Window
    {
    public:
        static Ref<Window> Create(const WindowProps& props);

        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& event) = 0;
        virtual std::any GetNativeWindow() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetVSync(bool state) = 0;
        virtual bool IsVSync() const = 0;

        virtual bool ShouldBeClosed() const = 0;
    protected:
        uint16_t p_WindowCount = 0;
    };
}

#endif //PANTHERA_WINDOW_HPP
