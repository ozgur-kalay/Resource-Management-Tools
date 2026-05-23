#pragma once

#include <wx/wx.h>

#include <cstdint>

class StatusPanel : public wxPanel
{
public:
    StatusPanel(wxWindow* parent);

#pragma region STATUS_UPDATES

    void SetStatusText(const wxString& statusText);
    void SetFileCount(std::size_t fileCount);
    void SetTotalSizeBytes(std::uintmax_t totalSizeBytes);

#pragma endregion STATUS_UPDATES

private:
#pragma region UI_CREATION

    void CreateUI();
    void CreateLayout();
    void CreateToolTips();

#pragma endregion UI_CREATION

#pragma region UI_WIDGETS

    wxStaticText* m_statusText = nullptr;
    wxStaticText* m_fileCountText = nullptr;
    wxStaticText* m_totalSizeText = nullptr;

#pragma endregion UI_WIDGETS
};