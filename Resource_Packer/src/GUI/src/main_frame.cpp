#include "main_frame.hpp"
#include <filesystem>
#include <algorithm>

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Resource Packer", wxDefaultPosition, wxSize(1200, 800))
{
    CreateFrameLayout();
    Centre();
}

#pragma region UI_CREATION

void MainFrame::CreateFrameLayout()
{
    m_rootPanel = new wxPanel(this);

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);

    CreateTopBar();
    CreateMainContent();
    CreateStatusArea();

    rootSizer->Add(m_topBar, 0, wxEXPAND);
    rootSizer->Add(m_mainContentPanel, 1, wxEXPAND);
    rootSizer->Add(m_statusPanel, 0, wxEXPAND);

    m_rootPanel->SetSizer(rootSizer);

    frameSizer->Add(m_rootPanel, 1, wxEXPAND);
    SetSizer(frameSizer);

    Layout();
}

void MainFrame::CreateTopBar()
{
    m_topBar = new TopBar(m_rootPanel);
}

void MainFrame::CreateMainContent()
{
    m_mainContentPanel = new wxPanel(m_rootPanel);

    wxBoxSizer* mainContentSizer = new wxBoxSizer(wxHORIZONTAL);

    CreateLeftControlPanel();
    CreateResourceListPanel();

    // mainContentSizer->Add(m_leftControlPanel, 0, wxEXPAND);
    // mainContentSizer->Add(m_resourceListPanel, 1, wxEXPAND);
    mainContentSizer->Add(m_leftControlPanel, 0, wxEXPAND | wxALL,0);
    mainContentSizer->Add(m_resourceListPanel, 1,wxEXPAND | wxALL, 0);

    m_mainContentPanel->SetSizer(mainContentSizer);
    m_mainContentPanel->Layout();
}

void MainFrame::CreateLeftControlPanel()
{
    m_leftControlPanel = new LeftControlPanel(m_mainContentPanel);

    m_leftControlPanel->BindAddFileButton(
        this,
        &MainFrame::OnAddFileClicked
    );

    m_leftControlPanel->BindAddDirectoryButton(
        this,
        &MainFrame::OnAddDirectoryClicked
    );
    m_leftControlPanel->BindRemoveSelectedButton(
        this,
        &MainFrame::OnRemoveSelectedClicked
    );
    m_leftControlPanel->BindRemoveAllButton(
        this,
        &MainFrame::OnRemoveAllClicked
    );
}

void MainFrame::CreateResourceListPanel()
{
    m_resourceListPanel = new ResourceListPanel(m_mainContentPanel);

    m_resourceListPanel->BindSortChoice(
        this,
        &MainFrame::OnSortModeChanged
    );
}

void MainFrame::CreateStatusArea()
{
    m_statusPanel = new StatusPanel(m_rootPanel);
}

#pragma endregion UI_CREATION

#pragma region EVENTS

void MainFrame::OnAddFileClicked(wxCommandEvent& event)
{
    wxFileDialog fileDialog(
        this,
        "Select resource files",
        wxEmptyString,
        wxEmptyString,
        "All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE
    );

    if (fileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxArrayString selectedPaths;
    fileDialog.GetPaths(selectedPaths);

    std::size_t addedFileCount = 0;
    std::size_t skippedDuplicateCount = 0;

    for (const wxString& selectedPath : selectedPaths)
    {
        if (m_resourceManager.ContainsSourcePath(selectedPath))
        {
            ++skippedDuplicateCount;
            continue;
        }

        std::filesystem::path filePath(
            selectedPath.ToStdWstring()
        );

        ResourceEntry entry;

        entry.fileName = filePath.filename().wstring();
        entry.sourcePath = selectedPath;
        entry.outputPath = "";
        entry.resourceReadPath = filePath.filename().wstring();

        if (std::filesystem::exists(filePath))
        {
            entry.fileSizeBytes = std::filesystem::file_size(filePath);
        }

        m_resourceManager.AddResource(entry);

        ++addedFileCount;
    }

    RefreshResourceUI();

    m_statusPanel->SetStatusText(
        wxString::Format(
            "Added %zu file(s), skipped %zu duplicate(s)",
            addedFileCount,
            skippedDuplicateCount
        )
    );

}

void MainFrame::OnAddDirectoryClicked(wxCommandEvent& event)
{
    wxDirDialog directoryDialog(
        this,
        "Select resource directory",
        wxEmptyString,
        wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST
    );

    if (directoryDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    std::filesystem::path selectedDirectory(
        directoryDialog.GetPath().ToStdWstring()
    );


    std::size_t addedFileCount = 0;
    std::size_t skippedDuplicateCount = 0;

    for (const std::filesystem::directory_entry& directoryEntry :
        std::filesystem::recursive_directory_iterator(selectedDirectory))
    {
        if (!directoryEntry.is_regular_file())
        {
            continue;
        }

        std::filesystem::path filePath = directoryEntry.path();

        wxString sourcePath = filePath.wstring();

        if (m_resourceManager.ContainsSourcePath(sourcePath))
        {
            ++skippedDuplicateCount;
            continue;
        }

        std::filesystem::path relativePath =
            std::filesystem::relative(filePath, selectedDirectory);

        ResourceEntry entry;

        entry.fileName = filePath.filename().wstring();
        entry.sourcePath = sourcePath;
        entry.outputPath = "";
        entry.resourceReadPath = relativePath.generic_wstring();

        if (std::filesystem::exists(filePath))
        {
            entry.fileSizeBytes = std::filesystem::file_size(filePath);
        }

        m_resourceManager.AddResource(entry);

        ++addedFileCount;
    }

    RefreshResourceUI();

    m_statusPanel->SetStatusText(
        wxString::Format(
            "Added %zu file(s) from directory, skipped %zu duplicate(s)",
            addedFileCount,
            skippedDuplicateCount
        )
    );
}

void MainFrame::OnSortModeChanged(wxCommandEvent& event)
{
    RefreshResourceList();

    if (m_resourceListPanel->GetSelectedSortMode() == ResourceSortMode::ByExtension)
    {
        m_statusPanel->SetStatusText("Resources sorted by extension");
        return;
    }

    m_statusPanel->SetStatusText("Default resource order restored");
}


void MainFrame::OnRemoveSelectedClicked(wxCommandEvent& event)
{
    std::vector<long> selectedRowIndices =
        m_resourceListPanel->GetSelectedRowIndices();

    if (selectedRowIndices.empty())
    {
        m_statusPanel->SetStatusText("No resources selected");
        return;
    }

    bool removed = m_resourceManager.RemoveResourcesAtIndices(
        selectedRowIndices
    );

    if (!removed)
    {
        m_statusPanel->SetStatusText("Failed to remove selected resources");
        return;
    }

    RefreshResourceUI();

    m_statusPanel->SetStatusText(
        wxString::Format(
            "Removed %zu resource(s)",
            selectedRowIndices.size()
        )
    );
}

void MainFrame::OnRemoveAllClicked(wxCommandEvent& event)
{
    if (m_resourceManager.GetResourceCount() == 0)
    {
        m_statusPanel->SetStatusText("No resources to remove");
        return;
    }

    m_resourceManager.ClearResources();

    RefreshResourceUI();

    m_statusPanel->SetStatusText(
        "All resources removed"
    );
}

#pragma endregion EVENTS

#pragma region UI_REFRESH

void MainFrame::RefreshResourceList()
{
    std::vector<ResourceEntry> displayResources =
        m_resourceManager.GetResources();

    ResourceSortMode sortMode =
        m_resourceListPanel->GetSelectedSortMode();

    if (sortMode == ResourceSortMode::ByExtension)
    {
        std::sort(
            displayResources.begin(),
            displayResources.end(),
            [](const ResourceEntry& a, const ResourceEntry& b)
            {
                std::filesystem::path pathA(a.fileName.ToStdWstring());
                std::filesystem::path pathB(b.fileName.ToStdWstring());

                return pathA.extension().wstring() < pathB.extension().wstring();
            }
        );
    }

    m_resourceListPanel->RefreshResources(displayResources);
}

void MainFrame::RefreshStatusPanel()
{
    m_statusPanel->SetFileCount(
        m_resourceManager.GetResourceCount()
    );

    m_statusPanel->SetTotalSizeBytes(
        m_resourceManager.GetTotalSizeBytes()
    );
}

void MainFrame::RefreshResourceUI()
{
    RefreshResourceList();
    RefreshStatusPanel();
}

#pragma endregion UI_REFRESH