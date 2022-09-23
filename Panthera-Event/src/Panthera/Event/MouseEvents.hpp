#ifndef PANTHERA_MOUSEEVENTS_HPP
#define PANTHERA_MOUSEEVENTS_HPP

#include "ppch.hpp"
#include "EventSystem.hpp"

namespace Panthera
{
    struct MouseButtonPressedEvent : public Event
    {
        int Button;

        MouseButtonPressedEvent(int button) : Button(button)
        {}

        EVENT_NAME("MouseButtonPressedEvent");
    };

    struct MouseButtonReleasedEvent : public Event
    {
        int Button;

        MouseButtonReleasedEvent(int button) : Button(button)
        {}

        EVENT_NAME("MouseButtonReleasedEvent");
    };

    struct MouseScrollEvent : public Event
    {
        double DeltaX, DeltaY;

        MouseScrollEvent(double deltaX, double deltaY) : DeltaX(deltaX), DeltaY(deltaY)
        {}

        EVENT_NAME("MouseScrollEvent");
    };

    struct MouseMoveEvent : public Event
    {
        float PosX, PosY;

        MouseMoveEvent(float posX, float posY) : PosX(posX), PosY(posY)
        {}

        EVENT_NAME("MouseMoveEvent");
    };

    struct MouseButtonEvent : public Event
    {
        int Button;

        MouseButtonEvent(int button) : Button(button)
        {}

        EVENT_NAME("MouseButtonEvent");
    };
}

#endif //PANTHERA_MOUSEEVENTS_HPP
