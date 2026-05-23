#pragma once

#include <wx/string.h>

#include <cstdint>

struct ResourceEntry
{
#pragma region RESOURCE_DATA

    wxString fileName;
    wxString sourcePath;
    wxString outputPath;
    wxString resourceReadPath;

    std::uintmax_t fileSizeBytes = 0;

#pragma endregion RESOURCE_DATA
};