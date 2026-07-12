#include "controls/res_table_buttons_controls.hpp"
#include "packing/pack_manager.hpp"
#include "controls/res_table_controls.hpp"
#include "wx/wfstream.h"

ResTableButtonsControls::ResTableButtonsControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();
}

void ResTableButtonsControls::_i_init_controls()
{
        // Initialize Buttons
    m_add_dir_button = new wxButton(this, wxID_ANY, "Add Directory", wxDefaultPosition, wxDefaultSize);

    m_add_file_button = new wxButton(this, wxID_ANY, "Add File", wxDefaultPosition, wxDefaultSize);

    m_remove_file_button = new wxButton(this, wxID_ANY, "Remove File", wxDefaultPosition, wxDefaultSize);
    //m_remove_file_button->Disable();

    int h_margin = 10;

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_add_dir_button);
    sizer->AddSpacer(h_margin);
    sizer->Add(m_add_file_button);
    sizer->AddSpacer(h_margin);
    sizer->Add(m_remove_file_button);

    SetSizer(sizer);
}

void ResTableButtonsControls::_i_connect_internal_events()
{
    m_add_dir_button->Bind(wxEVT_BUTTON, &ResTableButtonsControls::_on_add_directory_button_pressed, this);
    m_add_file_button->Bind(wxEVT_BUTTON, &ResTableButtonsControls::_on_add_file_button_pressed, this);
    m_remove_file_button->Bind(wxEVT_BUTTON, &ResTableButtonsControls::_on_remove_file_button_pressed, this);

}

void ResTableButtonsControls::_i_connect_external_events()
{
    
}

void ResTableButtonsControls::_on_add_directory_button_pressed(wxCommandEvent& event)
{
    wxString log = "ResourceTableButtons::_on_add_directory_button_pressed: Event: string = " + event.GetString();
    wxLogDebug(log);

    wxDirDialog openDirDialog(this, "Add Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (openDirDialog.ShowModal() != wxID_OK)
    {
        wxLogDebug("COULD NOT OPEN DIR DIALOG");
        return;
    }

    std::string dir_path_str = openDirDialog.GetPath().ToStdString();
    std::replace(dir_path_str.begin(), dir_path_str.end(), '\\', '/');
    std::filesystem::path dir_path(dir_path_str);

    m_dir_added_event.emit(dir_path);
}

void ResTableButtonsControls::_on_add_file_button_pressed(wxCommandEvent& event)
{ 
    wxFileDialog openFileDialog(this, "Add file", "", "","", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() != wxID_OK)
    {
        wxLogDebug("COULD NOT OPEN FILE DIALOG");
        return;
    }

    std::string path_str = openFileDialog.GetPath().ToStdString();
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    std::filesystem::path path(path_str);

    m_file_added_event.emit(path);
}

void ResTableButtonsControls::_on_remove_file_button_pressed(wxCommandEvent& event)
{
    wxString log = "ResourceTableButtons::_on_remove_file_button_pressed: Event: string = " + event.GetString();
    wxLogDebug(log);
}




