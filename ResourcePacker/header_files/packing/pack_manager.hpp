#ifndef RES_PACKER_PACK_MANAGER_HPP
#define RES_PACKER_PACK_MANAGER_HPP

#include "enums.hpp"
#include <wx/string.h>
#include <map>
#include <string>
#include "pack_parameters.hpp"
#include "custom_events.hpp"
#include <filesystem>

class PackManager
{
public:
    PackManager();

    static PackParameters& GetPackParams();
private:
    static PackParameters m_pack_params;
    wxString m_default_file_extention_str = "pack";

    //wxString GetDefaultFileExtentionStr() const;

// Custom Events Subscriptions
private:
    EventSystem::Subscription m_event_sub_packing_choices_changed;
    EventSystem::Subscription m_event_sub_pack_file_name_added;
    EventSystem::Subscription m_event_sub_pack_file_extention_added; // NOTE: Must add the default extention if the arg string is empty.
    EventSystem::Subscription m_event_sub_output_dir_changed;
    EventSystem::Subscription m_event_sub_access_name_choice_changed;
    EventSystem::Subscription m_event_sub_res_dir_added;
    EventSystem::Subscription m_event_sub_res_file_added;

    void _on_event_packing_choice_changed(Enums::PackingChoices packing_choice);
    void _on_event_pack_file_name_added(wxString& pack_file_name);
    void _on_event_pack_file_extention_added(wxString& file_extention);

    void _on_event_output_dir_changed(wxString& output_dir_path);

    void _on_event_access_name_choice_changed(Enums::AccessNameChoices access_name_choice);
    void _on_event_res_dir_added(std::filesystem::path& dir_path);
    void _on_event_res_file_added(std::filesystem::path& file_path);

// Pack flags
private:

    uint8_t m_ready_to_pack_flags = 0;
    
    const uint8_t ALL_FLAGS_READY = static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILE_NAME) | static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILE_EXTENTION)|static_cast<uint8_t>(Enums::PackReadyFlags::HAS_OUTPUT_DIR)|static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILES_TO_PACK);

    void _add_pack_ready_flag(Enums::PackReadyFlags condition);

// Custom Events
private:
    EventPackManagerReadyToPack m_event_pack_ready;

// Custom Event Subscribtions
private:
    EventSystem::Subscription m_event_sub_list_table_empty;

    void _on_event_list_table_empty();
};

#endif // RES_PACKER_PACK_MANAGER_HPP