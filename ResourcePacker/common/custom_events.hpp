#pragma once
#include "event_system.hpp"
#include "enums.hpp"
#include <filesystem>
#include "wx/string.h"


// Output Dir Events
class Event_OutputDirChanged : public EventSystem::Event<Event_OutputDirChanged, wxString&>{};


// Pack File Name And extention Events
class Event_PackFileNameAdded: public EventSystem::Event<Event_PackFileNameAdded, wxString&>{};
class Event_PackFileExtentionAdded: public EventSystem::Event<Event_PackFileExtentionAdded, wxString&>{};


// Packing Choices
class Event_PackingChoicesChanged : public EventSystem::Event<Event_PackingChoicesChanged, Enums::PackingChoices>{};

// Access name Choices
class Event_AccessNameChoicesChanged: public EventSystem::Event<Event_AccessNameChoicesChanged, Enums::AccessNameChoices>{};

// Resource added events
class Event_ResDirAdded : public EventSystem::Event<Event_ResDirAdded, std::filesystem::path&>{};
class Event_ResFileAdded : public EventSystem::Event<Event_ResFileAdded, std::filesystem::path&>{};


class EventListItemSelected: public EventSystem::Event<EventListItemSelected, long>{};

class EventListItemDESelected: public EventSystem::Event<EventListItemDESelected, long>{};

class EventListTableEmtpy: public EventSystem::Event<EventListTableEmtpy>{};


class EventRemoveListItemPressed: public EventSystem::Event<EventRemoveListItemPressed, long>{};

class EventPackManagerReadyToPack: public EventSystem::Event<EventPackManagerReadyToPack>{};