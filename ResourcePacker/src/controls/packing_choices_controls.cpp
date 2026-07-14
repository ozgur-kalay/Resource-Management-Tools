#include "controls/packing_choices_controls.hpp"
#include "packing/pack_manager.hpp"


PackingChoicesControls::PackingChoicesControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();
}

void PackingChoicesControls::_i_init_controls()
{
    m_packing_choices_array.Add("Pack Single File");
    m_packing_choices_array.Add("Pack Idividual Files");

    m_packing_choice = Enums::PackingChoices::PACK_SINGLE_FILE;

    m_packing_choices_label = new wxStaticText(this, wxID_ANY, "Packing options");

    m_packing_choices_ctrl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_packing_choices_array);
    m_packing_choices_ctrl->Select((int)m_packing_choice);

    _i_update_pack_data();

    // Initialize Sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_packing_choices_label);
    sizer->Add(m_packing_choices_ctrl);

    SetSizer(sizer);
}

void PackingChoicesControls::_i_connect_internal_events()
{
    m_packing_choices_ctrl->Bind(wxEVT_CHOICE, &PackingChoicesControls::_on_packing_choices_changed, this);
}

void PackingChoicesControls::_i_connect_external_events()
{

}

void PackingChoicesControls::_i_update_pack_data()
{
    m_packing_choice_changed_event.emit(m_packing_choice);
    
    wxString log = wxString::Format("Packing Choice updated: choice = %d", PackManager::GetPackParams().packing_choice);
    wxLogDebug(log);
}

void PackingChoicesControls::_on_packing_choices_changed(wxCommandEvent& event)
{
    m_packing_choice = (Enums::PackingChoices)event.GetInt();
    _i_update_pack_data();
}