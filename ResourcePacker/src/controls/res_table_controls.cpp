#include "controls/res_table_controls.hpp"
#include "config.hpp"
#include "packing/pack_manager.hpp"

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
    m_file_added_subscription = EventSystem::EventManager::get_instance().subscribe<FileAddedEvent>(this, &ResTableListControls::_on_file_added_event);
}

        // int idx = null_idx;
        // wxString resource_name;
        // wxString access_path;
        // wxString in_path;
        // wxString out_path;
        // float in_size = 0;
        // float out_size = 0;


void ResTableListControls::_on_file_added_event(std::filesystem::path path)
{
    wxString log = wxString::Format("FileAddedEvent recieved: event args = %s", path.string());
    wxLogDebug(log);
}

void ResTableListControls::AddFileToRow(std::filesystem::path file_path)
{
    auto _get_out_path = [](std::filesystem::path file_path)
    {
        PackManager& pack_man = PackManager::GetInstance();
        wxString outpath(pack_man.GetPackData().output_dir_path + "/");

        switch (pack_man.GetPackData().packing_choice)
        {
            case Enums::PackingChoices::PACK_SINGLE_FILE:
                outpath.append(pack_man.GetPackData().pack_file_name);
                break;
            case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
                outpath.append(file_path.filename().string());
                break;
        }

        return outpath;
    };


    ListRow row;
    row.resource_name = wxString(file_path.filename().string());
    row.access_path = row.resource_name;
    row.in_path = wxString(file_path.string());
    row.out_path = _get_out_path(file_path);
    row.in_size = std::filesystem::file_size(file_path);
    row.out_size = std::filesystem::file_size(file_path);

    wxLogDebug(row.GetString("Row"));
}

void ResTableListControls::AddDirToRows(std::filesystem::path dir_path)
{

}

