#ifndef PANTHERA_KEYBOARDEVENTS_HPP
#define PANTHERA_KEYBOARDEVENTS_HPP

#include "ppch.hpp"
#include "EventSystem.hpp"

namespace Panthera
{
    struct KeyPressedEvent : public Event
    {
        int Key;
        bool Repeated;

        KeyPressedEvent(int key, bool repeated) : Key(key), Repeated(repeated)
        {}

        EVENT_NAME("KeyPressedEvent");
    };

    struct KeyReleasedEvent : public Event
    {
        int Key;

        KeyReleasedEvent(int key) : Key(key)
        {}

        EVENT_NAME("KeyReleasedEvent");
    };

    struct KeyTypedEvent : public Event
    {
        uint32_t Key;

        KeyTypedEvent(uint32_t key) : Key(key)
        {}

        EVENT_NAME("KeyTypedEvent");
    };
}

#endif //PANTHERA_KEYBOARDEVENTS_HPP
