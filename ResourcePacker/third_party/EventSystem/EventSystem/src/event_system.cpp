#include "event_system.hpp"

namespace EventSystem
{
    EventManager& EventManager::get_instance()
    {
        static EventManager instance;
        return instance;
    }
}