#pragma once

#include <wx/wx.h>

class TopBar : public wxPanel
{
public:
    TopBar(wxWindow* parent);

private:
#pragma region UI_CREATION

    void CreateUI();
    void CreateLayout();

#pragma endregion UI_CREATION

#pragma region UI_WIDGETS

    wxStaticText* m_titleText = nullptr;

#pragma endregion UI_WIDGETS
};