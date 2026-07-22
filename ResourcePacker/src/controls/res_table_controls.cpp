#include "controls/res_table_controls.hpp"
#include "config.hpp"
#include "packing/pack_manager.hpp"
#include <string>

ResTableListControls::ResTableListControls(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    _i_init_controls();
    _i_connect_internal_events();
    _i_connect_external_events();

}

void ResTableListControls::_i_init_controls()
{    
    // Initialize List Control
    m_list_ctrl = new wxListCtrl(this, wxID_ANY, wxPoint(), Config::Sizes::RESOURCE_LIST, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_EDIT_LABELS);
    
    m_access_path_col_label = "Access Path";
    m_res_col_label = "Resource";
    m_origin_col_label = "Origin file";
    m_output_col_label = "Output file";
    m_in_size_col_label = "Input Size";
    m_out_size_col_label = "Output Size";

    m_access_path_col_width = 400;
    m_res_name_col_width = 200;
    m_origin_col_width = 200;
    m_output_col_width = 200;
    m_in_size_col_width = 200;
    m_out_size_col_width = 200;

    wxListItem access_path_col;
    access_path_col.SetId(ColumnIDS::ACCESS_PATH);
    access_path_col.SetText(m_access_path_col_label);
    access_path_col.SetWidth(m_access_path_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::ACCESS_PATH, access_path_col);

    wxListItem res_name_col;
    res_name_col.SetId(ColumnIDS::RESOURCE_NAME);
    res_name_col.SetText(m_res_col_label);
    res_name_col.SetWidth(m_res_name_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::RESOURCE_NAME, res_name_col);

    wxListItem origin_col;
    origin_col.SetId(ColumnIDS::IN_PATH);
    origin_col.SetText(m_origin_col_label);
    origin_col.SetWidth(m_origin_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::IN_PATH, origin_col);

    wxListItem output_col;
    output_col.SetId(ColumnIDS::OUT_PATH);
    output_col.SetText(m_output_col_label);
    output_col.SetWidth(m_output_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::OUT_PATH, output_col);

    wxListItem in_size_col;
    in_size_col.SetId(ColumnIDS::IN_SIZE);
    in_size_col.SetText(m_in_size_col_label);
    in_size_col.SetWidth(m_in_size_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::IN_SIZE, in_size_col);

    wxListItem out_size_col;
    out_size_col.SetId(ColumnIDS::OUT_SIZE);
    out_size_col.SetText(m_out_size_col_label);
    out_size_col.SetWidth(m_out_size_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::OUT_SIZE, out_size_col);

    // Initialize Sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(5);
    sizer->Add(m_list_ctrl); 

    SetSizer(sizer);
}


void ResTableListControls::_i_connect_internal_events()
{ 
    m_list_ctrl->Bind(wxEVT_LIST_ITEM_SELECTED, &ResTableListControls::_on_list_item_selected, this);
    m_list_ctrl->Bind(wxEVT_LIST_ITEM_DESELECTED, &ResTableListControls::_on_list_item_DEselected, this);
    m_list_ctrl->Bind(wxEVT_TEXT, &ResTableListControls::_on_access_name_changed, this);
}

void ResTableListControls::_i_connect_external_events()
{
    // m_event_sub_resource_dir_added = EventSystem::EventManager::get_instance().subscribe<Event_ResourceDirAdded>(this, &ResTableListControls::_on_event_resource_dir_added);
    // m_event_sub_single_resource_file_added = EventSystem::EventManager::get_instance().subscribe<Event_SingleResourceFileAdded>(this, &ResTableListControls::_on_event_single_resource_file_added);
    // m_event_sub_remove_list_item_pressed = EventSystem::EventManager::get_instance().subscribe<Event_RemoveResTableItemPressed>(this, &ResTableListControls::_on_event_remove_list_item_pressed);
    // m_event_sub_undo_pressed = EventSystem::EventManager::get_instance().subscribe<Event_UndoAddFiles>(this, &ResTableListControls::_on_undo_add_files_pressed);
}

void ResTableListControls::_on_access_name_changed(wxCommandEvent& event)
{
    wxString log = wxString::Format("ResTableListControls Access name changed = %s", event.GetString());
    wxLogDebug(log);
}

void ResTableListControls::_on_list_item_selected(wxListEvent& event)
{
    wxString log = wxString::Format("List item selected: index = %ld, col = %d", event.GetIndex(), event.GetColumn());
    wxLogDebug(log);

    m_list_item_selected_event.emit(event.GetIndex());
}

void ResTableListControls::_on_list_item_DEselected(wxListEvent& event)
{
    m_list_item_DEselected_event.emit(event.GetInt());
}





























// void ResTableListControls::_on_event_resource_dir_added(std::filesystem::path& dir_path)
// {
//     m_root_dir_name.clear();
//     m_root_dir_name = wxString(dir_path.filename().string());
//     _add_dir_to_rows(dir_path);
    
//     //wxString path = wxString::FromUTF8(dir_path.generic_string());
//     // wxLogDebug("ResTableListControls::DirAddedEvent received: event args = %s", path);
//     // wxLogDebug("dir_path.empty() = %d", static_cast<int>(dir_path.empty()));
// }

// void ResTableListControls::_on_event_single_resource_file_added(std::filesystem::path& path)
// {
//     m_root_dir_name.clear();
//     m_root_dir_name = wxString(path.parent_path().filename().string());
//     ResourceEntry& res_entry = _create_resource_entry(m_root_dir_name, path);
//     _insert_resource_entry_to_table(res_entry);

//     wxString log = wxString::Format("EventFileAdded recieved: event args = %s", wxString(path.c_str()));
//     wxLogDebug(log);
// }

// void ResTableListControls::_add_resource_file(std::filesystem::path file_path, bool single_file)
// {
//     wxString _root_name_dir;

//     if (single_file)
//     {
//         _root_name_dir = wxString(file_path.parent_path().filename().string());
//     } else{
//         //_root_name_dir = wxString(dir_path.filename().string());

//     }
// }

// void ResTableListControls::_on_event_remove_list_item_pressed(long idx)
// {   
//     wxMessageDialog* _confirm_delete_dialog = new wxMessageDialog(this,
//         "Are you sure you want to remove the item from the list?", "Confirm Delete", wxOK | wxCANCEL
//     );

//     _confirm_delete_dialog->SetOKCancelLabels("Remove", "Cancel");

//     if (_confirm_delete_dialog->ShowModal() != wxID_OK)
//     {
//         return;
//     }

//     m_list_ctrl->DeleteItem(idx);

//     if (m_list_ctrl->GetItemCount() <= 0)
//     {
//         m_list_table_empty.emit();
//     }
// }

// void ResTableListControls::_add_dir_to_rows(std::filesystem::path dir_path)
// {
//     std::filesystem::recursive_directory_iterator dir_iter(dir_path);

//     for (auto& dir_entry : dir_iter)
//     {
//         if (dir_entry.is_regular_file())
//         {
//             ResourceEntry& res_entry = _create_resource_entry(m_root_dir_name, dir_entry);
//             _insert_resource_entry_to_table(res_entry);
//         }
//     }
// }

// ResourceEntry& ResTableListControls::_create_resource_entry(wxString& root_dir_name, std::filesystem::path file_path)
// {
//     ResourceEntry res_entry(root_dir_name, file_path);
//     res_entry.SetIdx(m_list_ctrl->GetItemCount());
//     m_resource_entries.push_back(res_entry);
//     return m_resource_entries.back();
// }


// void ResTableListControls::_insert_resource_entry_to_table(ResourceEntry& res_entry)
// {
//     m_list_ctrl->InsertItem(res_entry.GetIdx(), res_entry.GetAccessPath()); // ColumnIDS::ACCESS_NAME
//     m_list_ctrl->SetItem(res_entry.GetIdx(), ColumnIDS::RESOURCE_NAME, res_entry.GetResourceName());
//     m_list_ctrl->SetItem(res_entry.GetIdx(), ColumnIDS::IN_PATH, res_entry.GetInPath());
//     m_list_ctrl->SetItem(res_entry.GetIdx(), ColumnIDS::OUT_PATH, res_entry.GetOutPath());
//     m_list_ctrl->SetItem(res_entry.GetIdx(), ColumnIDS::IN_SIZE, res_entry.GetInSizeStr());
//     m_list_ctrl->SetItem(res_entry.GetIdx(), ColumnIDS::OUT_SIZE, res_entry.GetOutSizeStr());   
// }


// void ResTableListControls::_on_undo_add_files_pressed()
// {
//     wxLogDebug("ResTableListControls recieved UNDO BUTOTN PRESED");
// }

