#pragma once

#include <wx/wx.h>

class ToolTipHelper
{
public:
#pragma region TOOLTIP_FUNCTIONS

    static void Attach(
        wxWindow* target,
        const wxString& message
    );

#pragma endregion TOOLTIP_FUNCTIONS
};