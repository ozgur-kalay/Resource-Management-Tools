#include "status_panel.hpp"
#include "tool_tip_helper.hpp"

StatusPanel::StatusPanel(wxWindow* parent)
    : wxPanel(parent)
{
    SetMinSize(wxSize(-1, 32));

    CreateUI();
    CreateLayout();
    CreateToolTips();
}

#pragma region UI_CREATION

void StatusPanel::CreateUI()
{
    m_statusText = new wxStaticText(
        this,
        wxID_ANY,
        "Ready"
    );

    m_fileCountText = new wxStaticText(
        this,
        wxID_ANY,
        "Files: 0"
    );

    m_totalSizeText = new wxStaticText(
        this,
        wxID_ANY,
        "Total Size: 0 bytes"
    );
}

void StatusPanel::CreateLayout()
{
    wxBoxSizer* rootSizer = new wxBoxSizer(wxHORIZONTAL);

    rootSizer->Add(
        m_statusText,
        0,
        wxALIGN_CENTER_VERTICAL | wxLEFT,
        12
    );

    rootSizer->AddStretchSpacer();

    rootSizer->Add(
        m_fileCountText,
        0,
        wxALIGN_CENTER_VERTICAL | wxRIGHT,
        20
    );

    rootSizer->Add(
        m_totalSizeText,
        0,
        wxALIGN_CENTER_VERTICAL | wxRIGHT,
        12
    );

    SetSizer(rootSizer);
}

void StatusPanel::CreateToolTips()
{
    ToolTipHelper::Attach(
        m_statusText,
        "Displays the current application status."
    );

    ToolTipHelper::Attach(
        m_fileCountText,
        "Shows the number of resources currently added."
    );

    ToolTipHelper::Attach(
        m_totalSizeText,
        "Shows the combined size of all resources currently added."
    );
}

#pragma endregion UI_CREATION

#pragma region STATUS_UPDATES

void StatusPanel::SetStatusText(const wxString& statusText)
{
    m_statusText->SetLabel(statusText);
}

void StatusPanel::SetFileCount(std::size_t fileCount)
{
    m_fileCountText->SetLabel(
        wxString::Format("Files: %zu", fileCount)
    );
}

void StatusPanel::SetTotalSizeBytes(std::uintmax_t totalSizeBytes)
{
    m_totalSizeText->SetLabel(
        wxString::Format("Total Size: %llu bytes", totalSizeBytes)
    );
}

#pragma endregion STATUS_UPDATES