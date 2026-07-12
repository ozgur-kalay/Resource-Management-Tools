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
    
    m_res_name_col_width = 200;
    m_access_path_col_width = 200;
    m_origin_col_width = 200;
    m_output_col_width = 200;
    m_in_size_col_width = 200;
    m_out_size_col_width = 200;
    
    m_res_col_label = "Resource Name";
    m_access_path_col_label = "Access Path";
    m_origin_col_label = "Origin file";
    m_output_col_label = "Output file";
    m_in_size_col_label = "Input Size";
    m_out_size_col_label = "Output Size";
    
    wxListItem res_name_col;
    res_name_col.SetId(ColumnIDS::RESOURCE_NAME);
    res_name_col.SetText(m_res_col_label);
    res_name_col.SetWidth(m_res_name_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::RESOURCE_NAME, res_name_col);

    wxListItem access_path_col;
    access_path_col.SetId(ColumnIDS::ACCESS_PATH);
    access_path_col.SetText(m_access_path_col_label);
    access_path_col.SetWidth(m_access_path_col_width);
    m_list_ctrl->InsertColumn(ColumnIDS::ACCESS_PATH, access_path_col);

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

}

void ResTableListControls::_i_connect_external_events()
{
    m_file_added_subscription = EventSystem::EventManager::get_instance().subscribe<EventFileAdded>(this, &ResTableListControls::_on_event_file_added);
    m_dir_added_subscription = EventSystem::EventManager::get_instance().subscribe<EventDirAdded>(this, &ResTableListControls::_on_event_dir_added);
}


void ResTableListControls::_on_event_dir_added(std::filesystem::path dir_path)
{
    wxString log = wxString::Format("DirAddedEvent recieved: event args = %s", dir_path.string());
    wxLogDebug(log);
    m_root_dir_name = wxString(dir_path.filename().string());
    _add_dir_to_rows(dir_path);
}

void ResTableListControls::_on_event_file_added(std::filesystem::path path)
{
    wxString log = wxString::Format("FileAddedEvent recieved: event args = %s", path.string());
    wxLogDebug(log);

    _add_file_to_row(path);
}


void ResTableListControls::_add_file_to_row(std::filesystem::path file_path)
{
    ListRow row(m_root_dir_name, file_path);
    _insert_row_to_list(row);
}

void ResTableListControls::_insert_row_to_list(ListRow row)
{
    row.SetIdx(m_list_ctrl->GetItemCount());
    m_list_ctrl->InsertItem(row.GetIdx(), row.GetResourceName()); // ColumnIDS::RESOURCE_NAME
    m_list_ctrl->SetItem(row.GetIdx(), ColumnIDS::ACCESS_PATH, row.GetAccessPath());
    m_list_ctrl->SetItem(row.GetIdx(), ColumnIDS::IN_PATH, row.GetInPath());
    m_list_ctrl->SetItem(row.GetIdx(), ColumnIDS::OUT_PATH, row.GetOutPath());
    m_list_ctrl->SetItem(row.GetIdx(), ColumnIDS::IN_SIZE, row.GetInSizeStr());
    m_list_ctrl->SetItem(row.GetIdx(), ColumnIDS::OUT_SIZE, row.GetOutSizeStr());
}

void ResTableListControls::_add_dir_to_rows(std::filesystem::path dir_path)
{
    std::filesystem::recursive_directory_iterator dir_iter(dir_path);

    for (auto& entry : dir_iter)
    {
        wxString log = wxString("entry: " + entry.path().string());
        wxLogDebug(log);
        if (entry.is_regular_file())
        {
            _add_file_to_row(entry);
        }
    }
}

