#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "resource_entry.hpp"
#include <vector>
#include "resource_sort_mode.hpp"

class ResourceListPanel : public wxPanel
{
public:
    ResourceListPanel(wxWindow* parent);

#pragma region RESOURCE_DISPLAY

    void RefreshResources(
        const std::vector<ResourceEntry>& resources
    );

#pragma endregion RESOURCE_DISPLAY

#pragma region SORT_ACCESS

    ResourceSortMode GetSelectedSortMode() const;

#pragma endregion SORT_ACCESS

#pragma region EVENT_BINDING

    template <typename OwnerType>
    void BindSortChoice(
        OwnerType* owner,
        void (OwnerType::*handler)(wxCommandEvent&)
    )
    {
        m_sortChoice->Bind(wxEVT_CHOICE, handler, owner);
    }

#pragma endregion EVENT_BINDING

#pragma region SELECTION_ACCESS

    long GetSelectedRowIndex() const;
    std::vector<long> GetSelectedRowIndices() const;

#pragma endregion SELECTION_ACCESS
private:
#pragma region UI_CREATION

    void CreateUI();
    void CreateLayout();
    void CreateColumns();
    void CreateToolbar();
    void CreateToolTips();

#pragma endregion UI_CREATION

#pragma region UI_WIDGETS

    wxListCtrl* m_resourceList = nullptr;
    wxPanel* m_toolbarPanel = nullptr;
    wxStaticText* m_sortLabel = nullptr;
    wxChoice* m_sortChoice = nullptr;

#pragma endregion UI_WIDGETS



};