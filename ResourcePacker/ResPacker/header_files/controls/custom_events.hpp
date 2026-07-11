#pragma once
#include "event_system.hpp"
#include <filesystem>


class FileAddedEvent : public EventSystem::Event<FileAddedEvent, std::filesystem::path>{};