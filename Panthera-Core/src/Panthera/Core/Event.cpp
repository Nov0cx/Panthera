#include "Event.hpp"

namespace Panthera
{
    void Event::SetCancelled(bool cancelled)
    {
        m_Cancelled = cancelled;
    }

    bool Event::IsCancelled() const
    {
        return m_Cancelled;
    }
}