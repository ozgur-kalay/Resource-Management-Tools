#pragma once

#include <wx/wx.h>

#include "top_bar.hpp"
#include "left_control_panel.hpp"
#include "resource_list_panel.hpp"
#include "status_panel.hpp"
#include "resource_manager.hpp"

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
#pragma region UI_CREATION

    void CreateFrameLayout();
    void CreateTopBar();
    void CreateMainContent();
    void CreateLeftControlPanel();
    void CreateResourceListPanel();
    void CreateStatusArea();

#pragma endregion UI_CREATION

#pragma region UI_WIDGETS

    wxPanel* m_rootPanel = nullptr;

    TopBar* m_topBar = nullptr;
    wxPanel* m_mainContentPanel = nullptr;
    LeftControlPanel* m_leftControlPanel = nullptr;
    ResourceListPanel* m_resourceListPanel = nullptr;
    StatusPanel* m_statusPanel = nullptr;

#pragma endregion UI_WIDGETS

#pragma region DATA

    ResourceManager m_resourceManager;

#pragma endregion DATA

#pragma region EVENTS

    void OnAddFileClicked(wxCommandEvent& event);
    void OnAddDirectoryClicked(wxCommandEvent& event);
    void OnSortModeChanged(wxCommandEvent& event);
    void OnRemoveSelectedClicked(wxCommandEvent& event);
    void OnRemoveAllClicked(wxCommandEvent& event);

#pragma endregion EVENTS

#pragma region UI_REFRESH

    void RefreshResourceList();
    void RefreshStatusPanel();
    void RefreshResourceUI();

#pragma endregion UI_REFRESH
};