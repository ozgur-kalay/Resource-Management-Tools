#ifndef RES_PACKER_RESOURCE_TABLE_BUTTONS_CONTROLS_HPP
#define RES_PACKER_RESOURCE_TABLE_BUTTONS_CONTROLS_HPP

#include "wx/wx.h"
#include "wx/filepicker.h"
#include "wx/listctrl.h"
#include "icontrol_initializer.hpp"

#include "custom_events.hpp"

class ResTableButtonsControls : public wxPanel, public IControlInitializer
{
    public:
        ResTableButtonsControls(wxWindow* parent);

    private:
        FileAddedEvent file_added_event;

        wxButton* m_add_dir_button;
        wxButton* m_add_file_button;
        wxButton* m_remove_file_button;

        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;

        void _on_add_directory_button_pressed(wxCommandEvent& event);
        void _on_add_file_button_pressed(wxCommandEvent& event);
        void _on_remove_file_button_pressed(wxCommandEvent& event);


};

#endif // RES_PACKER_RESOURCE_TABLE_BUTTONS_CONTROLS_HPP