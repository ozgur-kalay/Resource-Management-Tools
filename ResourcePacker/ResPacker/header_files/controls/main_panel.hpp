#ifndef RES_PACKER_APP_BODY_HPP
#define RES_PACKER_APP_BODY_HPP
#include "wx/wx.h"

class MainPanel : public wxPanel
{
    public:
        MainPanel(wxWindow* parent);
    private:
        void _init_sizer();
};

#endif // RES_PACKER_APP_BODY_HPP