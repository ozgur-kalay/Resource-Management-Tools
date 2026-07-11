#ifndef RES_PACKER_PACK_FILE_NAME_CONTROLS_HPP
#define RES_PACKER_PACK_FILE_NAME_CONTROLS_HPP
#include "wx/wx.h"
#include "icontrol_initializer.hpp"

class PackFileNameControls : public wxPanel, public IControlInitializer
{
    public:
        PackFileNameControls(wxWindow* parent);
    private:
        wxStaticText* m_pack_file_name_label;
        wxTextCtrl* m_file_name_txt_ctrl;

        wxStaticText* m_extension_dot_label;

        wxStaticText* m_file_extention_label;
        wxTextCtrl* m_file_extention_txt_ctrl;

        wxString m_pack_file_name_str;
        wxString m_pack_file_extention_str;

    private: 
        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;
        void _i_update_pack_data() override;

        void _on_file_name_entered(wxCommandEvent& event);
        void _on_file_extention_entered(wxCommandEvent& event);
};

#endif // RES_PACKER_PACK_FILE_NAME_CONTROLS_HPP