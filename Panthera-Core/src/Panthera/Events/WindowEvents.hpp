#ifndef RASPBERRYENGINE_WINDOWEVENTS_HPP
#define RASPBERRYENGINE_WINDOWEVENTS_HPP

#include "Panthera/Core/Event.hpp"

namespace Raspberry
{
    struct WindowResizeEvent : public Event
    {
        int Width, Height;

        WindowResizeEvent(int width, int height) : Width(width), Height(height)
        {}

        EVENT_TYPE(WindowResizeEvent)
        EventInformation("WindowResizeEvent", EventType::WINDOW)
    };
}

#endif //RASPBERRYENGINE_WINDOWEVENTS_HPP
