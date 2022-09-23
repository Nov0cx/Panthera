#ifndef PANTHERA_EVENTSYSTEM_HPP
#define PANTHERA_EVENTSYSTEM_HPP

#include "ppch.hpp"

namespace Panthera
{
    class Event
    {
    public:
        virtual ~Event() = default;

        virtual bool IsCancelled() const = 0;
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

#endif //PANTHERA_EVENTSYSTEM_HPP
