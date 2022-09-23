#include "EventSystem.hpp"

namespace Panthera
{
    struct EventManagerData
    {
        std::unordered_map<std::type_index, std::vector<std::function<void(Event&)>>> Listeners;
    };

    static EventManagerData s_EventManagerData;

    void EventManager::Init()
    {
        s_EventManagerData.Listeners.clear();
    }

    template<typename T>
    void EventManager::RegisterListener(const std::function<void(T &)> &listener)
    {
        static_assert(std::is_base_of<Event, T>::value, "T must be derived from Event");
        s_EventManagerData.Listeners[std::type_index(typeid(T))].push_back([listener](Event& event)
        {
            listener(static_cast<T&>(event));
        });
    }

    void EventManager::DispatchEvent(Event &event)
    {
        auto& listeners = s_EventManagerData.Listeners[std::type_index(typeid(event))];
        for (auto& listener : listeners)
        {
            listener(event);
        }
    }
}