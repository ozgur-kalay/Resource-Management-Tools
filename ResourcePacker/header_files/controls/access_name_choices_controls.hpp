#ifndef RES_PACKER_RESOURCE_ACCESS_CONTROLS_HPP
#define RES_PACKER_RESOURCE_ACCESS_CONTROLS_HPP

#include "wx/wx.h"
#include "icontrol_initializer.hpp"
#include "enums.hpp"
#include "custom_events.hpp"

class AccessNameChoicesControls : public wxPanel, public IControlInitializer
{
    public:
        AccessNameChoicesControls(wxWindow* parent);

    // Custom Events
    private:
        Event_AccessNameChoicesChanged m_event_access_name_choice_changed;
        
    private:
        Enums::AccessNameChoices m_access_name_choice;
    
        wxStaticText* m_access_name_choices_label;
        wxChoice* m_access_name_choices_ctrl;

        wxArrayString m_res_access_choices_list;

        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;

        void _i_update_pack_data() override;

        void _on_access_name_choice_changed(wxCommandEvent& event);
};

#endif // RES_PACKER_RESOURCE_ACCESS_CONTROLS_HPP