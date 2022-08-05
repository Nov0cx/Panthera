#ifndef RASPBERRYENGINE_MOUSEEVENTS_HPP
#define RASPBERRYENGINE_MOUSEEVENTS_HPP

#include "Panthera/Core/Event.hpp"

namespace Panthera
{
    struct MouseButtonPressedEvent : public Event
    {
        int Button;

        MouseButtonPressedEvent(int button) : Button(button)
        {}

        EVENT_TYPE(MouseButtonPressedEvent)
        EventInformation("MouseButtonPressedEvent", EventType::MOUSE)
    };

    struct MouseButtonReleasedEvent : public Event
    {
        int Button;

        MouseButtonReleasedEvent(int button) : Button(button)
        {}

        EVENT_TYPE(MouseButtonReleasedEvent)
        EventInformation("MouseButtonReleasedEvent", EventType::MOUSE)
    };


    struct MouseScrollEvent : public Event
    {
        double PosX, PosY;

        MouseScrollEvent(double posX, double posY) : PosX(posX), PosY(posY)
        {}

        EVENT_TYPE(MouseScrollEvent)
        EventInformation("MouseScrollEvent", EventType::MOUSE)
    };

    struct MouseMoveEvent : public Event
    {
        double PosX, PosY;

        MouseMoveEvent(double posX, double posY) : PosX(posX), PosY(posY)
        {}

        EVENT_TYPE(MouseMoveEvent)
        EventInformation("MouseMoveEvent", EventType::MOUSE)
    };
}

#endif //RASPBERRYENGINE_MOUSEEVENTS_HPP
