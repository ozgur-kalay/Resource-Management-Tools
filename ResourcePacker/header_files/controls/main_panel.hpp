#ifndef RES_PACKER_APP_BODY_HPP
#define RES_PACKER_APP_BODY_HPP
#include "wx/wx.h"
#include "packing/pack_manager.hpp"

class MainPanel : public wxPanel
{
    public:
        MainPanel(wxWindow* parent);
    private:
        void _init_sizer();
        PackManager m_pack_manager;
};

#endif // RES_PACKER_APP_BODY_HPP