#pragma once
#include "enums.hpp"
#include "resource_types.hpp"
#include <wx/string.h>
#include <map>
#include <string>

struct PackParameters
{
    Enums::PackingChoices packing_choice;
    wxString pack_file_name;
    wxString pack_file_extention;
    wxString pack_output_dir_path;
    Enums::AccessNameChoices access_name_choice;

    // {Resource name with extension, access name}
    std::map<std::string, std::string> access_names_glossery;
};