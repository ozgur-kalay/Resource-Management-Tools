#include "controls/output_dir_controls.hpp"
#include "packing/pack_manager.hpp"


OutputDirControls::OutputDirControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();
}


void OutputDirControls::_i_init_controls()
{
    m_output_dir_label = new wxStaticText(this, wxID_ANY, "Output Directory", wxPoint(), wxDefaultSize);
    m_output_dir_picker_ctrl = new wxDirPickerCtrl(this, wxID_ANY, "Select dir", "Select Directory", wxDefaultPosition, wxSize(500, 25), wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

    // Initialize Sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_output_dir_label);
    sizer->Add(m_output_dir_picker_ctrl);

    SetSizer(sizer);
}



void OutputDirControls::_i_connect_internal_events()
{
    m_output_dir_picker_ctrl->Bind(wxEVT_DIRPICKER_CHANGED, &OutputDirControls::_on_dir_picker_changed, this);
}

void OutputDirControls::_i_connect_external_events()
{

}

void OutputDirControls::_i_update_pack_data()
{
    m_output_dir_str.Replace("\\", "/");

    PackManager::GetInstance().AddOutputDir(m_output_dir_str);

    wxString log = wxString::Format("Output Dir update: output dir = %s", PackManager::GetInstance().GetPackData().output_dir_path);
    wxLogDebug(log);
}

void OutputDirControls::_on_dir_picker_changed(wxFileDirPickerEvent& event)
{
    m_output_dir_str = event.GetPath();
    _i_update_pack_data();
}
