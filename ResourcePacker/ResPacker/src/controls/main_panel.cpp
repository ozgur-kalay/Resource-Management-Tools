#include "controls/main_panel.hpp"

#include "controls/packing_choices_controls.hpp"
#include "controls/pack_file_name_controls.hpp"
#include "controls/output_dir_controls.hpp"
#include "controls/res_access_path_choices_controls.hpp"
#include "controls/res_table_buttons_controls.hpp"
#include "controls/res_table_controls.hpp"

MainPanel::MainPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY)
{
    PackingChoicesControls* packing_choices = new PackingChoicesControls(this);
    PackFileNameControls* pack_file_name = new PackFileNameControls(this);
    OutputDirControls* output_dir = new OutputDirControls(this);
    ResAccessPathChoicesControls* resource_access = new ResAccessPathChoicesControls(this);
    ResTableButtonsControls *res_table_buttons = new ResTableButtonsControls(this);
    ResTableListControls* res_table_list = new ResTableListControls(this);

    int top_margin = 20;
    int left_margin = 10;

    int seperation = 25;

    int res_table_margin = 3;

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(top_margin);
    sizer->Add(packing_choices, 0, wxLEFT, left_margin);
    sizer->AddSpacer(seperation);
    sizer->Add(pack_file_name, 0, wxLEFT, left_margin);
    sizer->AddSpacer(seperation);
    sizer->Add(output_dir, 0, wxLEFT, left_margin);
    sizer->AddSpacer(seperation);
    sizer->Add(resource_access, 0, wxLEFT, left_margin);
    sizer->AddSpacer(seperation);
    sizer->Add(res_table_buttons,0, wxLEFT, left_margin);
    sizer->AddSpacer(res_table_margin);
    sizer->Add(res_table_list, 0, wxLEFT, left_margin);

    SetSizerAndFit(sizer);
}