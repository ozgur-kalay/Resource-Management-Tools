#include "top_bar.hpp"

TopBar::TopBar(wxWindow* parent)
    : wxPanel(parent)
{
    SetMinSize(wxSize(-1, 56));

    CreateUI();
    CreateLayout();
}

#pragma region UI_CREATION

void TopBar::CreateUI()
{
    m_titleText = new wxStaticText(
        this,
        wxID_ANY,
        "Resource Packer"
    );
}

void TopBar::CreateLayout()
{
    wxBoxSizer* rootSizer = new wxBoxSizer(wxHORIZONTAL);

    rootSizer->Add(
        m_titleText,
        0,
        wxALIGN_CENTER_VERTICAL | wxLEFT,
        12
    );

    SetSizer(rootSizer);
}

#pragma endregion UI_CREATION