#ifndef PANTHERA_WINDOWEVENTS_HPP
#define PANTHERA_WINDOWEVENTS_HPP

#include "ppch.hpp"
#include "EventSystem.hpp"

namespace Panthera
{
    struct WindowResizeEvent : public Event
    {
        int Width, Height;

        WindowResizeEvent(int width, int height) : Width(width), Height(height)
        {}

        EVENT_NAME("WindowResizeEvent");
    };

    struct WindowCloseEvent : public Event
    {
        EVENT_NAME("WindowCloseEvent");
    };
}

#endif //PANTHERA_WINDOWEVENTS_HPP
