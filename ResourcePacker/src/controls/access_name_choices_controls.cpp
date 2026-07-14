#include "controls/access_name_choices_controls.hpp"
#include "packing/pack_manager.hpp"

AccessNameChoicesControls::AccessNameChoicesControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();
}

void AccessNameChoicesControls::_i_init_controls()
{
    m_res_access_choices_list.Add("Relative to root");
    //m_res_access_choices_list.Add("Full Path");
    m_res_access_choices_list.Add("File Name Only");

    m_access_name_choice = Enums::AccessNameChoices::RELATIVE_TO_ROOT;

    m_access_name_choices_label = new wxStaticText(this, wxID_ANY, "Resource Access Path");
    m_access_name_choices_ctrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_res_access_choices_list);
    m_access_name_choices_ctrl->Select((int)m_access_name_choice);

    _i_update_pack_data();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_access_name_choices_label);
    sizer->Add(m_access_name_choices_ctrl);

    SetSizer(sizer);
}

void AccessNameChoicesControls::_i_connect_internal_events()
{
    m_access_name_choices_ctrl->Bind(wxEVT_CHOICE, &AccessNameChoicesControls::_on_access_name_choice_changed, this);
}

void AccessNameChoicesControls::_i_connect_external_events()
{
    
}

void AccessNameChoicesControls::_i_update_pack_data()
{
    m_event_access_name_choice_changed.emit(m_access_name_choice);

    //wxString log = wxString::Format("Access name choice updated: access name choice: ");

    switch (m_access_name_choice)
    {
        case Enums::AccessNameChoices::RELATIVE_TO_ROOT:
            //log.append(wxString::Format("enum = %d, string = RELATIVE_TO_ROOT", (int)Enums::AccessNameChoices::RELATIVE_TO_ROOT));
            break;
        case Enums::AccessNameChoices::FULL_PATH:
            //log.append(wxString::Format("enum = %d, string = FULL_PATH", (int)Enums::AccessNameChoices::FULL_PATH));
            break;
        case Enums::AccessNameChoices::FILE_NAME_ONLY:
            //log.append(wxString::Format("enum = %d, string = FILE_NAME_ONLY", (int)Enums::AccessNameChoices::FILE_NAME_ONLY));
            break;
    }

    //wxLogDebug(log);
}

void AccessNameChoicesControls::_on_access_name_choice_changed(wxCommandEvent& event)
{
    m_access_name_choice = (Enums::AccessNameChoices)event.GetInt();
    _i_update_pack_data();
}