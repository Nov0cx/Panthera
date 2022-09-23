#ifndef PANTHERA_WINDOWEVENTS_HPP
#define PANTHERA_WINDOWEVENTS_HPP

#include "ppch.hpp"
#include "EventSystem.hpp"

namespace Panthera
{
    struct WindowResizeEvent : public Event
    {
        uint32_t Width, Height;

        WindowResizeEvent(uint32_t width, uint32_t height) : Width(width), Height(height)
        {}

        EVENT_NAME("WindowResizeEvent");
    };
}

#endif //PANTHERA_WINDOWEVENTS_HPP
