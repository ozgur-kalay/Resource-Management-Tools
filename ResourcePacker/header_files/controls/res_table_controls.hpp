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

    static std::vector<ListRow> rows;

    public:
        ResTableListControls(wxWindow* parent);

    // Members
    private:
        enum ColumnIDS : uint8_t {RESOURCE_NAME, ACCESS_PATH, IN_PATH, OUT_PATH, IN_SIZE, OUT_SIZE};

        int m_res_name_col_width;
        int m_access_path_col_width;
        int m_origin_col_width;
        int m_output_col_width;
        int m_in_size_col_width;
        int m_out_size_col_width;

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
        
    // Events Handling
    private:
        EventSystem::Subscription m_file_added_subscription;
        EventSystem::Subscription m_dir_added_subscription;
        
        void _on_event_dir_added(std::filesystem::path dir_path);
        void _on_event_file_added(std::filesystem::path file_path);
        
    // Helpers
    private:
        void _add_file_to_row(std::filesystem::path file_path);
        void _add_dir_to_rows(std::filesystem::path dir_path);

        void _insert_row_to_list(ListRow row);
};

#endif // RES_PACKER_RESOURCE_TABLE_PANEL_HPPf