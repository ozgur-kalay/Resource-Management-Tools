#ifndef RES_PACKER_PACK_MANAGER_HPP
#define RES_PACKER_PACK_MANAGER_HPP

#include "enums.hpp"
#include <wx/string.h>
#include <map>
#include <string>
#include "packing_parameters.hpp"
#include "packing_data.hpp"
#include "custom_events.hpp"
#include <filesystem>

class PackManager
{
public:
    PackManager();

    static const PackingParameters& GetPackParams();

// Data Packing
private:
    static PackingParameters m_pack_params;
    static PackingData m_packing_data;
    
    wxString m_default_file_extention_str = "pack";

    void _add_file(std::filesystem::path file_path, wxString root_name = {});

// Custom Events Subscriptions
private:
    EventSystem::Subscription m_event_sub_packing_choices_changed;
    EventSystem::Subscription m_event_sub_pack_file_name_added;
    EventSystem::Subscription m_event_sub_pack_file_extention_added; // NOTE: Must add the default extention if the arg string is empty.
    EventSystem::Subscription m_event_sub_output_dir_changed;
    EventSystem::Subscription m_event_sub_access_name_choice_changed;
    EventSystem::Subscription m_event_sub_resource_dir_added;
    EventSystem::Subscription m_event_sub_single_resource_file_added;
    //EventSystem::Subscription m_event_sub_res_table_emtpy;

    EventSystem::Subscription m_event_sub_create_pack_pressed;

    void _on_event_packing_choice_changed(Enums::PackingChoices packing_choice);
    void _on_event_pack_file_name_added(wxString& pack_file_name);
    void _on_event_pack_file_extention_added(wxString& file_extention);

    void _on_event_output_dir_changed(wxString& output_dir_path);

    void _on_event_access_name_choice_changed(Enums::AccessNameChoices access_name_choice);
    void _on_event_res_dir_added(std::filesystem::path& dir_path);
    void _on_event_res_file_added(std::filesystem::path& file_path);
    void _on_event_res_table_empty();

    void _on_event_create_pack();

// Pack flags
private:

    uint8_t m_pack_ready_flags = 0;
    
    const uint8_t SINGLE_FILE_PACKING_READY = static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILE_NAME) | static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILE_EXTENTION)|static_cast<uint8_t>(Enums::PackReadyFlags::HAS_OUTPUT_DIR)|static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILES_TO_PACK);
    const uint8_t INDIVIDUAL_PACKING_READY = static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILE_EXTENTION) | static_cast<uint8_t>(Enums::PackReadyFlags::HAS_OUTPUT_DIR)|static_cast<uint8_t>(Enums::PackReadyFlags::HAS_FILES_TO_PACK);

    void _add_pack_ready_flag(Enums::PackReadyFlags flag);
    void _remove_pack_ready_flag(Enums::PackReadyFlags flag);

// Custom Events
private:
    
    Event_PackManagerReadyToPack m_event_pack_ready;

    void _check_and_publish_pack_ready();

// Custom Event Subscribtions
private:
    EventSystem::Subscription m_event_sub_list_table_empty;

    void _on_event_list_table_empty();
};

#endif // RES_PACKER_PACK_MANAGER_HPP