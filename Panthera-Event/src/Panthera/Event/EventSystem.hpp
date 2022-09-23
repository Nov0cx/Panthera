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

    class EventManager
    {
    public:
        static void Init();
        template<typename T>
        static void RegisterListener(const std::function<void(T&)>& listener);
        static void DispatchEvent(Event& event);
    };
}

#define EVENT_NAME(name) virtual String GetDebugName() const override { return name; }

#endif //PANTHERA_EVENTSYSTEM_HPP
