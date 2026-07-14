#ifndef RES_PACKER_RESOURCE_TABLE_PANEL_HPP
#define RES_PACKER_RESOURCE_TABLE_PANEL_HPP

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "icontrol_initializer.hpp"
#include <filesystem>
#include <vector>
#include "null_idx.hpp"


#include "custom_events.hpp"
#include "classes/list_row.hpp"




class ResTableListControls : public wxPanel, public IControlInitializer
{
    // RESOURCE_NAME, ACCESS_PATH, IN_PATH, OUT_PATH, IN_SIZE, OUT_SIZE

    std::vector<ListRow> m_rows;

    public:
        ResTableListControls(wxWindow* parent);

    // Members
    private:
        enum ColumnIDS : uint8_t {ACCESS_PATH, RESOURCE_NAME, IN_PATH, OUT_PATH, IN_SIZE, OUT_SIZE};

        unsigned int m_res_name_col_width;
        unsigned int m_access_path_col_width;
        unsigned int m_origin_col_width;
        unsigned int m_output_col_width;
        unsigned int m_in_size_col_width;
        unsigned int m_out_size_col_width;

        wxString m_res_col_label;
        wxString m_access_path_col_label;
        wxString m_origin_col_label;
        wxString m_output_col_label;
        wxString m_in_size_col_label;
        wxString m_out_size_col_label;

        wxButton* m_add_dir_button;
        wxButton* m_add_file_button;
        wxButton* m_remove_file_button;
        wxListCtrl* m_list_ctrl;

        wxString m_root_dir_name;

    // Initializers
    private:
        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;
    // Custom Events
    private:
        EventListItemSelected m_list_item_selected_event;
        EventListItemDESelected m_list_item_DEselected_event;
        EventListTableEmtpy m_list_table_empty;
    // Custom Events Subscribtions
    private:
        EventSystem::Subscription m_event_sub_dir_added;
        EventSystem::Subscription m_event_sub_file_added;
        EventSystem::Subscription m_event_sub_remove_list_item_pressed;
        
        void _on_event_dir_added(std::filesystem::path& dir_path);
        void _on_event_file_added(std::filesystem::path& file_path);
        void _on_event_remove_list_item_pressed(long idx);
    // Wx Events handling
    private:
        void _on_list_item_selected(wxListEvent& event);
        void _on_list_item_DEselected(wxListEvent& event);
        void _on_access_name_changed(wxCommandEvent& event);
    // Helpers
    private:
        void _add_dir_to_rows(std::filesystem::path dir_path);

        void _insert_row_to_list(wxString& root_dir_name, std::filesystem::path file_path);

        //void _display_dir_content(std::filesystem::path dir_path);
};

#endif // RES_PACKER_RESOURCE_TABLE_PANEL_HPPf