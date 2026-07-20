#include "wx/wx.h"
#include "main_frame.hpp"

#ifdef __WXMSW__
    #include <windows.h>
#endif

class ResourcePacker : public wxApp
{
public:
    bool OnInit() override;
};

bool ResourcePacker::OnInit()
{
#ifdef __WXMSW__
    SetProcessDpiAwarenessContext(
        DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
    );
#endif

    MainFrame* main_frame = new MainFrame();
    main_frame->Show();

    return true;
}

wxIMPLEMENT_APP(ResourcePacker);



// #include "wx/wx.h"
// #include "main_frame.hpp"

// class ResourcePacker : public wxApp
// {
//     public:
//         bool OnInit() override;
// };

// bool ResourcePacker::OnInit()
// {
//     MainFrame* main_frame = new MainFrame();
//     main_frame->Show();
//     return true;
// }

// wxIMPLEMENT_APP(ResourcePacker);