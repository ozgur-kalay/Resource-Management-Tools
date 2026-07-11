#include "wx/wx.h"
#include "main_frame.hpp"

class ResourcePacker : public wxApp
{
    public:
        bool OnInit() override;
};

bool ResourcePacker::OnInit()
{
    MainFrame* main_frame = new MainFrame();
    main_frame->Show();
    return true;
}

wxIMPLEMENT_APP(ResourcePacker);