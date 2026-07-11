#include "controls/res_access_path_choices_controls.hpp"
#include "packing/pack_manager.hpp"

ResAccessPathChoicesControls::ResAccessPathChoicesControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();
}

void ResAccessPathChoicesControls::_i_init_controls()
{
    m_res_access_choices_list.Add("Relative to root");
    m_res_access_choices_list.Add("Full Path");
    m_res_access_choices_list.Add("File Name Only");

    m_access_name_choice = Enums::ResAccessPathChoices::RELATIVE_TO_ROOT;

    m_access_name_choices_label = new wxStaticText(this, wxID_ANY, "Resource Access Path");
    m_access_name_choices_ctrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_res_access_choices_list);
    m_access_name_choices_ctrl->Select((int)m_access_name_choice);

    _i_update_pack_data();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_access_name_choices_label);
    sizer->Add(m_access_name_choices_ctrl);

    SetSizer(sizer);
}

void ResAccessPathChoicesControls::_i_connect_internal_events()
{
    m_access_name_choices_ctrl->Bind(wxEVT_CHOICE, &ResAccessPathChoicesControls::_on_access_name_choice_changed, this);
}

void ResAccessPathChoicesControls::_i_connect_external_events()
{
    
}

void ResAccessPathChoicesControls::_i_update_pack_data()
{
    PackManager::GetInstance().AddAccessNameChoice(m_access_name_choice);

    wxString log = wxString::Format("Access name choice updated: access name choice: ");

    switch (m_access_name_choice)
    {
        case Enums::ResAccessPathChoices::RELATIVE_TO_ROOT:
            log.append(wxString::Format("enum = %d, string = RELATIVE_TO_ROOT", (int)Enums::ResAccessPathChoices::RELATIVE_TO_ROOT));
            break;
        case Enums::ResAccessPathChoices::FULL_PATH:
            log.append(wxString::Format("enum = %d, string = FULL_PATH", (int)Enums::ResAccessPathChoices::FULL_PATH));
            break;
        case Enums::ResAccessPathChoices::FILE_NAME_ONLY:
            log.append(wxString::Format("enum = %d, string = FILE_NAME_ONLY", (int)Enums::ResAccessPathChoices::FILE_NAME_ONLY));
            break;
    }
    wxLogDebug(log);
}

void ResAccessPathChoicesControls::_on_access_name_choice_changed(wxCommandEvent& event)
{
    m_access_name_choice = (Enums::ResAccessPathChoices)event.GetInt();
    _i_update_pack_data();
}