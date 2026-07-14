#include "packing/pack_manager.hpp"
#include "wx/wx.h"

PackParameters PackManager::m_pack_params;

PackParameters& PackManager::GetPackParams(){return m_pack_params;}

PackManager::PackManager()
{
    m_event_sub_packing_choices_changed = EventSystem::EventManager::get_instance().subscribe<Event_PackingChoicesChanged>(this, &PackManager::_on_event_packing_choice_changed);
    m_event_sub_pack_file_name_added = EventSystem::EventManager::get_instance().subscribe<Event_PackFileNameAdded>(this, &PackManager::_on_event_pack_file_name_added);
    m_event_sub_pack_file_extention_added = EventSystem::EventManager::get_instance().subscribe<Event_PackFileExtentionAdded>(this, &PackManager::_on_event_pack_file_extention_added); // NOTE: Must add the default extention if the arg string is empty.
    m_event_sub_output_dir_changed = EventSystem::EventManager::get_instance().subscribe<Event_OutputDirChanged>(this, &PackManager::_on_event_output_dir_changed);
    m_event_sub_access_name_choice_changed = EventSystem::EventManager::get_instance().subscribe<Event_AccessNameChoicesChanged>(this, &PackManager::_on_event_access_name_choice_changed);
    m_event_sub_res_dir_added = EventSystem::EventManager::get_instance().subscribe<Event_ResDirAdded>(this, &PackManager::_on_event_res_dir_added);
    m_event_sub_res_file_added = EventSystem::EventManager::get_instance().subscribe<Event_ResFileAdded>(this, &PackManager::_on_event_res_file_added);
}

void PackManager::_on_event_packing_choice_changed(Enums::PackingChoices packing_choice)
{
    m_pack_params.packing_choice = packing_choice;
}

void PackManager::_on_event_pack_file_name_added(wxString& pack_file_name)
{
    m_pack_params.pack_file_name = pack_file_name;

    _add_pack_ready_flag(Enums::PackReadyFlags::HAS_FILE_NAME);

    wxString log = wxString::Format("PackManager::_on_event_pack_file_name_added: pack file name = %s", pack_file_name);
    wxLogDebug(log);
}

void PackManager::_on_event_pack_file_extention_added(wxString& file_extention)
{
    if (file_extention.IsEmpty())
    {
        m_pack_params.pack_file_extention = m_default_file_extention_str;
    } else{
        m_pack_params.pack_file_extention = file_extention;
    }

    _add_pack_ready_flag(Enums::PackReadyFlags::HAS_FILE_EXTENTION);

    wxString log = wxString::Format("PackManager::_on_event_pack_file_extention_added: pack file extention = %s", file_extention);
    wxLogDebug(log);
}

void PackManager::_on_event_output_dir_changed(wxString& output_dir_path)
{
    m_pack_params.pack_output_dir_path = output_dir_path;

    _add_pack_ready_flag(Enums::PackReadyFlags::HAS_OUTPUT_DIR);

    wxString log = wxString::Format("PackManager:: output dir changed recieved: dir = %s", output_dir_path);
    wxLogDebug(log);
}

void PackManager::_on_event_access_name_choice_changed(Enums::AccessNameChoices access_name_choice)
{
    m_pack_params.access_name_choice = access_name_choice;
}

void PackManager::_add_pack_ready_flag(Enums::PackReadyFlags condition)
{
    m_ready_to_pack_flags |= static_cast<uint8_t>(condition);

    if (m_ready_to_pack_flags == ALL_FLAGS_READY)
    {
        wxLogDebug("PackManager:: READY TO PACK!!!");
        m_event_pack_ready.emit();
    } else{
        wxLogDebug("PackManager::Pack NOT ready: pack state = %d : required = %d", m_ready_to_pack_flags, ALL_FLAGS_READY);
    }
}

void PackManager::_on_event_res_dir_added(std::filesystem::path& dir_path)
{
    _add_pack_ready_flag(Enums::PackReadyFlags::HAS_FILES_TO_PACK);

    wxString log = wxString::Format("PackManager::_on_event_res_dir_added:: dir path = %s", dir_path.string());
    wxLogDebug(log);
}

void PackManager::_on_event_res_file_added(std::filesystem::path& file_path)
{
    _add_pack_ready_flag(Enums::PackReadyFlags::HAS_FILES_TO_PACK);
}