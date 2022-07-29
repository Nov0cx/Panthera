#ifndef PANTHERA_EVENT_HPP
#define PANTHERA_EVENT_HPP

#include <functional>
#include <vector>
#include <initializer_list>

namespace Panthera
{
    enum class EventType
    {
        NONE = 0, WINDOW, KEY, MOUSE
    };

    enum class EventSubType
    {
        KeyPressedEvent = 0, KeyReleasedEvent, KeyTypedEvent,
        MouseButtonReleasedEvent, MouseButtonPressedEvent, MouseScrollEvent,
        MouseMoveEvent, WindowResizeEvent
    };

    //fwd
    class Window;

    class Event
    {
    public:
        template<typename T>
        class Listener
        {
        public:
            Listener(const std::function<void(T& event)>& func) : m_Function(func) {};

            inline void Run(Event& e, EventSubType type) const
            {
                if (e.GetEventSubType() == type) m_Function(reinterpret_cast<T&>(e));
            }
        private:
            std::function<void(T& event)> m_Function;
        };

    public:
        Event() = default;

        virtual ~Event() = default;

        virtual void SetCancelled(bool cancelled);

        [[nodiscard]] virtual bool IsCancelled() const;

        virtual EventSubType GetEventSubType() const = 0;

        inline virtual const char* GetName() const { return ""; }
        inline virtual EventType GetEventType() const { return EventType::NONE; }

    private:
        bool m_Cancelled = false;
    };
}

#define EVENT_TYPE(Type) inline virtual EventSubType GetEventSubType() const override { return EventSubType::Type; }
#define EventInformation(name, type) \
        inline virtual const char* GetName() const override { return name; } \
        inline virtual EventType GetEventType() const override { return type; }

#endif //PANTHERA_EVENT_HPP
