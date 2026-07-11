#ifndef RES_PACKER_RESOURCE_TABLE_PANEL_HPP
#define RES_PACKER_RESOURCE_TABLE_PANEL_HPP

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "icontrol_initializer.hpp"
#include <filesystem>
#include <vector>
#include "null_idx.hpp"

#include "controls/custom_events.hpp"

class ResTableListControls : public wxPanel, public IControlInitializer
{
    // RESOURCE_NAME, ACCESS_PATH, IN_PATH, OUT_PATH, IN_SIZE, OUT_SIZE
    struct ListRow
    {
        int idx = null_idx;
        wxString resource_name;
        wxString access_path;
        wxString in_path;
        wxString out_path;
        float in_size = 0;
        float out_size = 0;

        wxString GetString(const wxString& title) const
        {
            return wxString::Format(
                    "ListRow: %s:\n"
                    "    idx = %d\n"
                    "    resource_name = %s\n"
                    "    access_path = %s\n"
                    "    in_path = %s\n"
                    "    out_path = %s\n"
                    "    in_size = %.2f\n"
                    "    out_size = %.2f",
                    title, idx, resource_name, access_path, in_path, out_path, in_size, out_size
                );
        }
    };

    static std::vector<ListRow> rows;

    public:
        ResTableListControls(wxWindow* parent);

        static void AddFileToRow(std::filesystem::path file_path);
        static void AddDirToRows(std::filesystem::path dir_path);

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


        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;

    // Events Handling
    private:
        EventSystem::Subscription m_file_added_subscription;
        void _on_file_added_event(std::filesystem::path path);

};

#endif // RES_PACKER_RESOURCE_TABLE_PANEL_HPP