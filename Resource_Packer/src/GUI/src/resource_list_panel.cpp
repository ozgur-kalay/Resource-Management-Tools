#include "resource_list_panel.hpp"

ResourceListPanel::ResourceListPanel(wxWindow* parent)
    : wxPanel(parent)
{
    CreateUI();
    CreateColumns();
    CreateToolbar();
    CreateLayout();
    CreateToolTips();
}

#pragma region UI_CREATION

void ResourceListPanel::CreateUI()
{
    m_resourceList = new wxListCtrl(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxLC_REPORT
    );
}

void ResourceListPanel::CreateLayout()
{
    wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);

    toolbarSizer->Add(
        m_sortLabel,
        0,
        wxALIGN_CENTER_VERTICAL | wxRIGHT,
        8
    );

    toolbarSizer->Add(
        m_sortChoice,
        0,
        wxALIGN_CENTER_VERTICAL
    );

    m_toolbarPanel->SetSizer(toolbarSizer);

    rootSizer->Add(
        m_toolbarPanel,
        0,
        wxLEFT | wxRIGHT | wxTOP,
        12
    );

    rootSizer->Add(
        m_resourceList,
        1,
        wxLEFT | wxRIGHT | wxBOTTOM,
        8
    );

    SetSizer(rootSizer);
}

void ResourceListPanel::CreateColumns()
{
    m_resourceList->AppendColumn(
        "File Name",
        wxLIST_FORMAT_LEFT,
        200
    );

    m_resourceList->AppendColumn(
        "Source Path",
        wxLIST_FORMAT_LEFT,
        200
    );

    m_resourceList->AppendColumn(
        "Output Path",
        wxLIST_FORMAT_LEFT,
        200
    );

    m_resourceList->AppendColumn(
        "Resource Read Path",
        wxLIST_FORMAT_LEFT,
        600
    );
}

void ResourceListPanel::CreateToolTips()
{
    m_resourceList->SetToolTip(
        "Columns:\n"
        "File Name: The file name only.\n"
        "Source Path: The real disk location.\n"
        "Output Path: Future packed output structure.\n"
        "Resource Read Path: Virtual runtime load path."
    );
}
void ResourceListPanel::CreateToolbar()
{
    m_toolbarPanel = new wxPanel(this);

    m_sortLabel = new wxStaticText(
        m_toolbarPanel,
        wxID_ANY,
        "Sort"
    );

    wxArrayString sortOptions;
    sortOptions.Add("Default");
    sortOptions.Add("By Extension");

    m_sortChoice = new wxChoice(
        m_toolbarPanel,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        sortOptions
    );

    m_sortChoice->SetSelection(0);
}
#pragma endregion UI_CREATION

#pragma region RESOURCE_DISPLAY

void ResourceListPanel::RefreshResources(
    const std::vector<ResourceEntry>& resources
)
{
    m_resourceList->DeleteAllItems();

    long rowIndex = 0;

    for (const ResourceEntry& resource : resources)
    {
        long insertedIndex = m_resourceList->InsertItem(
            rowIndex,
            resource.fileName
        );

        m_resourceList->SetItem(
            insertedIndex,
            1,
            resource.sourcePath
        );

        m_resourceList->SetItem(
            insertedIndex,
            2,
            resource.outputPath
        );

        m_resourceList->SetItem(
            insertedIndex,
            3,
            resource.resourceReadPath
        );

        ++rowIndex;
    }
}

#pragma endregion RESOURCE_DISPLAY

#pragma region SORT_ACCESS

ResourceSortMode ResourceListPanel::GetSelectedSortMode() const
{
    int selection = m_sortChoice->GetSelection();

    if (selection == 1)
    {
        return ResourceSortMode::ByExtension;
    }

    return ResourceSortMode::Default;
}

#pragma endregion SORT_ACCESS

#pragma region SELECTION_ACCESS

long ResourceListPanel::GetSelectedRowIndex() const
{
    return m_resourceList->GetNextItem(
        -1,
        wxLIST_NEXT_ALL,
        wxLIST_STATE_SELECTED
    );
}

std::vector<long> ResourceListPanel::GetSelectedRowIndices() const
{
    std::vector<long> selectedRows;

    long currentItem = -1;

    while (true)
    {
        currentItem = m_resourceList->GetNextItem(
            currentItem,
            wxLIST_NEXT_ALL,
            wxLIST_STATE_SELECTED
        );

        if (currentItem == -1)
        {
            break;
        }

        selectedRows.push_back(currentItem);
    }

    return selectedRows;
}
#pragma endregion SELECTION_ACCESS