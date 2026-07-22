#pragma once
#include "enums.hpp"
#include <wx/string.h>
#include <map>
#include <string>
#include <vector>


struct PackingParameters
{
    Enums::PackingChoices packing_choice;
    wxString pack_file_name;
    wxString pack_file_extention;
    wxString pack_output_dir_path;
    Enums::AccessNameChoices access_name_choice;
};