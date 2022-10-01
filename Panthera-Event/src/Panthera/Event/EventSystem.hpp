#ifndef PANTHERA_EVENTSYSTEM_HPP
#define PANTHERA_EVENTSYSTEM_HPP

#include "ppch.hpp"

namespace Panthera
{
    class Event
    {
    public:
        virtual ~Event() = default;

        virtual bool IsCancelled() const { return m_IsCancelled; };
        virtual void Cancel() { m_IsCancelled = true; };
        virtual String GetDebugName() const { return "Event"; }
    protected:
        bool m_IsCancelled = false;
    };

    enum class EventPriority
    {
        Lowest = 0,
        Low,
        Normal,
        High,
        Highest
    };

    class EventManager
    {
    public:
        static void Init();
        template<typename T>
        static void RegisterListener(const std::function<void(T&)>& listener, EventPriority priority = EventPriority::NORMAL);
        static void DispatchEvent(Event& event);
    };

    struct EventListener
    {
        EventListener(std::type_index type, const std::function<void(Event&)>& listener, EventPriority priority)
            : Type(type), Listener(listener), Priority(priority) {}

        std::type_index Type;
        std::function<void(Event&)> Listener;
        EventPriority Priority;
    };

    struct EventManagerData
    {
        std::vector<EventListener> Listeners;

        static EventManagerData *Instance;
    };

    inline void EventManager::Init()
    {
        if (EventManagerData::Instance == nullptr)
            EventManagerData::Instance = new EventManagerData();
        EventManagerData::Instance->Listeners.clear();
        PT_LOG_INFO("Event Manager initialized");
    }

    template<typename T>
    inline void EventManager::RegisterListener(const std::function<void(T &)> &listener, EventPriority priority)
    {
        static_assert(std::is_base_of<Event, T>::value, "T must be derived from Event");
        EventManagerData::Instance->Listeners.push_back(EventListener(typeid(T), [listener](Event& event) { listener(static_cast<T&>(event)); }, priority));
        PT_LOG_INFO("Registered listener for event {}", typeid(T).name());
        std::sort(EventManagerData::Instance->Listeners.begin(), EventManagerData::Instance->Listeners.end(),
                  [](const EventListener& a, const EventListener& b) { return (int)a.Priority > (int)b.Priority; });
    }

    inline void EventManager::DispatchEvent(Event &event)
    {
        for (auto& listener : EventManagerData::Instance->Listeners)
        {
            PT_LOG_INFO("Listener type {}", listener.Type.name());
            if (listener.Type == typeid(event))
            {
                listener.Listener(event);
                if (event.IsCancelled())
                    break;
            }
        }
    }
}

#define EVENT_NAME(name) virtual String GetDebugName() const override { return name; }

#endif //PANTHERA_EVENTSYSTEM_HPP
