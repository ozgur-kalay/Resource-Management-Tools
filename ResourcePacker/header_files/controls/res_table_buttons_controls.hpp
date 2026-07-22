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

    // Custom events
    private:
        Event_ResourceDirAdded m_event_dir_added_event;
        Event_SingleResourceFileAdded m_event_single_resource_file_added_event;
        Event_RemoveResTableItemPressed m_event_remove_list_item_pressed;
        Event_UndoAddFiles m_event_undo_pressed;

        Event_CreatePackPressed m_event_create_pack_pressed;

        long m_selected_item_idx = -1;

        EventSystem::Subscription m_event_sub_list_item_selected;
        EventSystem::Subscription m_event_sub_list_item_DE_selected;
        EventSystem::Subscription m_event_sub_list_table_emtpy;
        EventSystem::Subscription m_event_sub_pack_ready;
        

        void _on_event_list_item_seleced(long idx);
        void _on_event_list_item_DE_seleced(long idx);
        void _on_event_list_table_empty();
        void _on_event_pack_ready();

    private:

        wxButton* m_add_dir_button;
        wxButton* m_add_file_button;
        wxButton* m_remove_file_button;
        wxButton* m_undo_add_items_button;
        wxButton* m_create_pack_button;
        wxMessageDialog* m_message_dialog;

        void _i_init_controls() override;
        void _i_connect_internal_events() override;
        void _i_connect_external_events() override;

        void _on_add_directory_button_pressed(wxCommandEvent& event);
        void _on_add_file_button_pressed(wxCommandEvent& event);
        void _on_remove_file_button_pressed(wxCommandEvent& event);
        void _on_undo_button_pressed(wxCommandEvent& event);
        void _on_create_pack_button_pressed(wxCommandEvent& event);

};

#endif // RES_PACKER_RESOURCE_TABLE_BUTTONS_CONTROLS_HPP