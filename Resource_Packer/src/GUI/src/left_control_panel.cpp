#include "left_control_panel.hpp"
#include "tool_tip_helper.hpp"

LeftControlPanel::LeftControlPanel(wxWindow* parent)
    : wxPanel(parent)
{
    SetMinSize(wxSize(260, -1));

    CreateUI();
    CreateLayout();
    CreateToolTips();
}

#pragma region UI_CREATION

void LeftControlPanel::CreateUI()
{
    m_addFileButton = new wxButton(this, wxID_ANY, "Add File");
    m_addDirectoryButton = new wxButton(this, wxID_ANY, "Add Directory");

    wxArrayString sortOptions;
    sortOptions.Add("Default");
    sortOptions.Add("By Extension");

    m_encryptionKeyLabel = new wxStaticText(this, wxID_ANY, "Encryption Key");

    m_encryptionKeyInput = new wxTextCtrl(this, wxID_ANY);

    m_packSingleFileCheckbox = new wxCheckBox(
        this,
        wxID_ANY,
        "Pack everything into one .resc file"
    );

    m_removeSelectedButton = new wxButton(
        this,
        wxID_ANY,
        "Remove Selected"
    );

    m_removeAllButton = new wxButton(
        this,
        wxID_ANY,
        "Remove All"
    );
}

void LeftControlPanel::CreateLayout()
{
    wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);

    rootSizer->Add(m_addFileButton, 0, wxEXPAND | wxALL, 8);
    rootSizer->Add(m_addDirectoryButton, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);

    rootSizer->Add(m_encryptionKeyLabel, 0, wxLEFT | wxRIGHT | wxTOP, 8);
    rootSizer->Add(m_encryptionKeyInput, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);

    rootSizer->Add(m_packSingleFileCheckbox, 0, wxEXPAND | wxALL, 8);

    rootSizer->Add(m_removeSelectedButton,0,wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,8);

    rootSizer->Add(m_removeAllButton,0,wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,8);

    SetSizer(rootSizer);
}

void LeftControlPanel::CreateToolTips()
{
    ToolTipHelper::Attach(
        m_addFileButton,
        "Adds individual files to the resource list. Folder structure is not preserved."
    );

    ToolTipHelper::Attach(
        m_addDirectoryButton,
        "Adds a directory recursively. Folder structure relative to the selected directory is preserved."
    );


    ToolTipHelper::Attach(
        m_encryptionKeyInput,
        "Optional key that will later be used for encrypted resource packing. The key is visible while typing."
    );

    ToolTipHelper::Attach(
        m_packSingleFileCheckbox,
        "When enabled, all resources will later be packed into one .resc file."
    );

    ToolTipHelper::Attach(
        m_removeSelectedButton,
        "Removes the currently selected resource from the list."
    );

    ToolTipHelper::Attach(
        m_removeAllButton,
        "Removes all resources from the current packer list."
    );
}

#pragma endregion UI_CREATION

