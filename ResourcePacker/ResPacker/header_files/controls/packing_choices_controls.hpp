#ifndef RES_PACKER_PACKING_CHOICES_CONTROLS_HPP
#define RES_PACKER_PACKING_CHOICES_CONTROLS_HPP
#include "wx/wx.h"
#include "icontrol_initializer.hpp"
#include "enums.hpp"

class PackingChoicesControls : public wxPanel, public IControlInitializer
{


    public:
        PackingChoicesControls(wxWindow* parent);
    
    private:
        Enums::PackingChoices m_packing_choice;

        wxArrayString m_packing_choices_array;
        
        wxStaticText* m_packing_choices_label;
        wxChoice* m_packing_choices_ctrl;

        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;
        void _i_update_pack_data() override;
        
        void _on_packing_choices_changed(wxCommandEvent& event);

};

#endif // RES_PACKER_PACKING_CHOICES_CONTROLS_HPP