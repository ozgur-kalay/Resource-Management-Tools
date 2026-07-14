#include "controls/pack_file_name_controls.hpp"
#include "packing/pack_manager.hpp"

PackFileNameControls::PackFileNameControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();
}

void PackFileNameControls::_i_init_controls()
{
    m_pack_file_name_str = "resources";
    m_pack_file_extention_str = "pack";

    m_pack_file_name_label = new wxStaticText(this, wxID_ANY, "Pack file name");
    m_file_extention_label = new wxStaticText(this, wxID_ANY, "Extension");

    m_file_name_txt_ctrl = new wxTextCtrl(this, wxID_ANY, m_pack_file_name_str);

    m_extension_dot_label = new wxStaticText(this, wxID_ANY, ".");
    m_file_extention_txt_ctrl = new wxTextCtrl(this, wxID_ANY, m_pack_file_extention_str);

    _i_update_pack_data();

    int left_padding = 2;
    // File name sizers
    wxBoxSizer* v_file_name_sizer = new wxBoxSizer(wxVERTICAL);
    v_file_name_sizer->Add(m_pack_file_name_label, 0, wxLEFT, left_padding);
    v_file_name_sizer->Add(m_file_name_txt_ctrl);

    // Extension Sizers
    wxBoxSizer* v_extention_sizer = new wxBoxSizer(wxVERTICAL);
    v_extention_sizer->Add(m_file_extention_label, 0, wxLEFT, left_padding);
    v_extention_sizer->Add(m_file_extention_txt_ctrl);
    
    

    // Main Sizer
    wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
    main_sizer->Add(v_file_name_sizer);
    main_sizer->Add(m_extension_dot_label, 0, wxALIGN_BOTTOM | wxBOTTOM, 4);
    main_sizer->Add(v_extention_sizer);
    
    SetSizer(main_sizer);
}

void PackFileNameControls::_i_connect_internal_events()
{
    m_file_name_txt_ctrl->Bind(wxEVT_TEXT, &PackFileNameControls::_on_file_name_entered, this);
    m_file_extention_txt_ctrl->Bind(wxEVT_TEXT, &PackFileNameControls::_on_file_extention_entered, this);
}

void PackFileNameControls::_i_connect_external_events()
{
    m_packing_choices_changed_subscription = EventSystem::EventManager::get_instance().subscribe<Event_PackingChoicesChanged>(this, &PackFileNameControls::_on_event_packing_choices_changed);
}

void PackFileNameControls::_i_update_pack_data()
{
    m_event_pack_file_name_added.emit(m_pack_file_name_str);
    m_event_pack_file_extention_added.emit(m_pack_file_extention_str);

    // wxString log = wxString::Format("PackFileNameControls::Pack file name changed: file name = %s", m_pack_file_name_str);
    // wxLogDebug(log);
}

void PackFileNameControls::_on_file_name_entered(wxCommandEvent& event)
{
    m_pack_file_name_str = event.GetString();
    _i_update_pack_data();
}

void PackFileNameControls::_on_file_extention_entered(wxCommandEvent& event)
{
    wxString _entered_string = event.GetString();

    m_pack_file_extention_str = _entered_string;

    _i_update_pack_data();
}

void PackFileNameControls::_on_event_packing_choices_changed(Enums::PackingChoices new_choice)
{
    wxString log = "PackFileNameControls::_on_packing_choices_changed: new choice = ";

    switch (new_choice)
    {
        case Enums::PackingChoices::PACK_SINGLE_FILE:
            m_pack_file_name_label->Enable();
            m_file_name_txt_ctrl->Enable();

            // m_file_extention_label->Enable();
            // m_file_extention_txt_ctrl->Enable();

            log.append("PACK_SINGLE_FILE");
            break;
        case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
            m_pack_file_name_label->Disable();
            m_file_name_txt_ctrl->Disable();
        
            // m_file_extention_label->Disable();
            // m_file_extention_txt_ctrl->Disable();
        
            log.append("PACK_INDIVIDUAL_FILES");
            break;
    }

    wxLogDebug(log);
}