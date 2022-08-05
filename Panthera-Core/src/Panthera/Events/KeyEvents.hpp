#ifndef RASPBERRYENGINE_KEYEVENTS_HPP
#define RASPBERRYENGINE_KEYEVENTS_HPP

#include "Panthera/Core/Event.hpp"

namespace Raspberry
{
    struct KeyPressedEvent : public Event
    {
        int Key;
        bool Repeated;

        KeyPressedEvent(int key, bool repeated) : Key(key), Repeated(repeated)
        {}

        EVENT_TYPE(KeyPressedEvent)
        EventInformation("KeyPressedEvent", EventType::KEY)
    };

    struct KeyReleasedEvent : public Event
    {
        int Key;

        KeyReleasedEvent(int key) : Key(key)
        {}

        EVENT_TYPE(KeyReleasedEvent)
        EventInformation("KeyReleasedEvent", EventType::KEY)
    };

    struct KeyTypedEvent : public Event
    {
        unsigned int Key;

        KeyTypedEvent(unsigned int key) : Key(key)
        {}

        EVENT_TYPE(KeyTypedEvent)
        EventInformation("KeyTypedEvent", EventType::KEY)
    };
}

#endif //RASPBERRYENGINE_KEYEVENTS_HPP
