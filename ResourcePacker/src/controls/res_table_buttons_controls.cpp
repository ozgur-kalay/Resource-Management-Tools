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
    m_add_dir_button = new wxButton(this, wxID_ANY, "Add Directory");
    m_add_file_button = new wxButton(this, wxID_ANY, "Add File");
    m_remove_file_button = new wxButton(this, wxID_ANY, "Remove File");
    m_remove_file_button->Disable();

    m_create_pack_button = new wxButton(this, wxID_ANY, "Create Pack");
    m_create_pack_button->Disable();

    m_message_dialog = new wxMessageDialog(this, "Resource Packer Error");

    int h_margin = 10;

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_add_dir_button);
    sizer->AddSpacer(h_margin);
    sizer->Add(m_add_file_button);
    sizer->AddSpacer(h_margin);
    sizer->Add(m_remove_file_button);
    sizer->AddSpacer(h_margin * 10);
    sizer->Add(m_create_pack_button);

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
    m_event_sub_list_item_selected = EventSystem::EventManager::get_instance().subscribe<EventListItemSelected>(this, &ResTableButtonsControls::_on_event_list_item_seleced);
    m_event_sub_list_item_DE_selected = EventSystem::EventManager::get_instance().subscribe<EventListItemDESelected>(this, &ResTableButtonsControls::_on_event_list_item_DE_seleced);
    m_event_sub_pack_ready = EventSystem::EventManager::get_instance().subscribe<EventPackManagerReadyToPack>(this, &ResTableButtonsControls::_on_event_pack_ready);
}

void ResTableButtonsControls::_on_add_directory_button_pressed(wxCommandEvent& event)
{
    if (PackManager::GetPackParams().pack_output_dir_path.IsEmpty())
    {
        m_message_dialog->SetMessage("Output dir must be set first!");
        m_message_dialog->ShowModal();
        return;
    }

    wxDirDialog openDirDialog(this, "Add Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (openDirDialog.ShowModal() != wxID_OK)
    {
        wxLogDebug("COULD NOT OPEN DIR DIALOG");
        return;
    }

    std::string dir_path_str = openDirDialog.GetPath().ToStdString();
    std::replace(dir_path_str.begin(), dir_path_str.end(), '\\', '/');
    std::filesystem::path dir_path(dir_path_str);

    // wxString log = wxString::Format("ResTableButtonsControls::m_event_dir_added_event.emit(dir_path) emitting with = %s", dir_path.string());
    // wxLogDebug(log);
    
    m_event_dir_added_event.emit(dir_path);
}

void ResTableButtonsControls::_on_add_file_button_pressed(wxCommandEvent& event)
{
    if (PackManager::GetPackParams().pack_output_dir_path.IsEmpty())
    {
        m_message_dialog->SetMessage("Output dir must be set first!");
        m_message_dialog->ShowModal();
        return;
    }

    wxFileDialog openFileDialog(this, "Add file", "", "","", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() != wxID_OK)
    {
        wxLogDebug("COULD NOT OPEN FILE DIALOG");
        return;
    }

    std::string path_str = openFileDialog.GetPath().ToStdString();
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    std::filesystem::path path(path_str);

    m_event_file_added_event.emit(path);
}

void ResTableButtonsControls::_on_remove_file_button_pressed(wxCommandEvent& event)
{
    wxString log = "ResourceTableButtons::_on_remove_file_button_pressed: Event: string = " + event.GetString();
    wxLogDebug(log);
    m_event_remove_list_item_pressed.emit(m_selected_item_idx);
}


void ResTableButtonsControls::_on_event_list_item_seleced(long idx)
{
    
    m_remove_file_button->Enable();
    m_selected_item_idx = idx;
}

void ResTableButtonsControls::_on_event_list_item_DE_seleced(long idx)
{
    //m_remove_file_button->Unbind(wxEVT_BUTTON, &ResTableButtonsControls::_on_remove_file_button_pressed, this);
    m_add_dir_button->SetFocus(); // Move focus to another button to prevent focus related artifect debug errors.
    
    m_remove_file_button->Disable();
    m_selected_item_idx = -1;
}

void ResTableButtonsControls::_on_event_pack_ready()
{
    m_create_pack_button->Enable();
}


