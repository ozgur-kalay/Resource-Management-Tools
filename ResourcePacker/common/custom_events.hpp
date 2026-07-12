#pragma once
#include "event_system.hpp"
#include "enums.hpp"
#include <filesystem>


class EventDirAdded : public EventSystem::Event<EventDirAdded, std::filesystem::path>{};

class EventFileAdded : public EventSystem::Event<EventFileAdded, std::filesystem::path>{};

class EventPackingChoicesChanged : public EventSystem::Event<EventPackingChoicesChanged, Enums::PackingChoices>{};