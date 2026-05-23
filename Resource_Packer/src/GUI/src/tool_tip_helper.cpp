#include "tool_tip_helper.hpp"

#pragma region TOOLTIP_FUNCTIONS

void ToolTipHelper::Attach(
    wxWindow* target,
    const wxString& message
)
{
    if (target == nullptr)
    {
        return;
    }

    target->SetToolTip(message);
}

#pragma endregion TOOLTIP_FUNCTIONS