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
class Event_ResourceDirAdded : public EventSystem::Event<Event_ResourceDirAdded, std::filesystem::path&>{};
class Event_SingleResourceFileAdded : public EventSystem::Event<Event_SingleResourceFileAdded, std::filesystem::path&>{};

class Event_UndoAddFiles : public EventSystem::Event<Event_UndoAddFiles>{};

class Event_ResTableItemSelected: public EventSystem::Event<Event_ResTableItemSelected, long>{};

class Event_ResTableItemDESelected: public EventSystem::Event<Event_ResTableItemDESelected, long>{};

//class Event_ResTableEmtpy: public EventSystem::Event<Event_ResTableEmtpy>{};

class Event_RemoveResTableItemPressed: public EventSystem::Event<Event_RemoveResTableItemPressed, long>{};

class Event_PackManagerReadyToPack: public EventSystem::Event<Event_PackManagerReadyToPack>{};

class Event_CreatePackPressed: public EventSystem::Event<Event_CreatePackPressed>{};