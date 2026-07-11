#include "main_frame.hpp"
#include "config.hpp"

#include "controls/main_panel.hpp"
//#include "resource_list.hpp"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Resource Packer")
{
    SetSize(Config::Sizes::WINDOW);
    CenterOnScreen();
    FromDIP(192);
    
    MainPanel* main_panel = new MainPanel(this);

    CreateStatusBar();

    //ResourceList* resource_list = new ResourceList(this);
}
