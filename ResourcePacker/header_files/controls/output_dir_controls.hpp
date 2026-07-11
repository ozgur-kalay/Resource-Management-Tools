#ifndef RES_PACKER_OUTPUT_DIR_CONTROLS_HPP
#define RES_PACKER_OUTPUT_DIR_CONTROLS_HPP

#include "wx/wx.h"
#include "wx/filepicker.h"
#include "icontrol_initializer.hpp"

class OutputDirControls : public wxPanel, public IControlInitializer
{
    public:
        OutputDirControls(wxWindow* parent);

    private:
        wxStaticText* m_output_dir_label;
        wxDirPickerCtrl* m_output_dir_picker_ctrl;

        wxString m_output_dir_str;

        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;
        void _i_update_pack_data() override;

        void _on_dir_picker_changed(wxFileDirPickerEvent& event);

};

#endif // RES_PACKER_OUTPUT_DIR_CONTROLS_HPP