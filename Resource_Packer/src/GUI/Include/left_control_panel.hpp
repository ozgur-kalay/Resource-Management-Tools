#pragma once

#include <wx/wx.h>

class LeftControlPanel : public wxPanel
{
public:
    LeftControlPanel(wxWindow* parent);

#pragma region EVENT_BINDING

    template <typename OwnerType>
    void BindAddFileButton(
        OwnerType* owner,
        void (OwnerType::*handler)(wxCommandEvent&)
    )
    {
        m_addFileButton->Bind(wxEVT_BUTTON, handler, owner);
    }

    template <typename OwnerType>
    void BindAddDirectoryButton(
        OwnerType* owner,
        void (OwnerType::*handler)(wxCommandEvent&)
    )
    {
        m_addDirectoryButton->Bind(wxEVT_BUTTON, handler, owner);
    }

    template <typename OwnerType>
    void BindRemoveSelectedButton(
        OwnerType* owner,
        void (OwnerType::*handler)(wxCommandEvent&)
    )
    {
        m_removeSelectedButton->Bind(wxEVT_BUTTON, handler, owner);
    }

    template <typename OwnerType>
    void BindRemoveAllButton(
        OwnerType* owner,
        void (OwnerType::*handler)(wxCommandEvent&)
    )
    {
        m_removeAllButton->Bind(wxEVT_BUTTON, handler, owner);
    }

#pragma endregion EVENT_BINDING

private:
#pragma region UI_CREATION

    void CreateUI();
    void CreateLayout();
    void CreateToolTips();

#pragma endregion UI_CREATION

#pragma region UI_WIDGETS

    wxButton* m_addFileButton = nullptr;
    wxButton* m_addDirectoryButton = nullptr;

    wxStaticText* m_encryptionKeyLabel = nullptr;
    wxTextCtrl* m_encryptionKeyInput = nullptr;

    wxCheckBox* m_packSingleFileCheckbox = nullptr;

    wxButton* m_removeSelectedButton = nullptr;

    wxButton* m_removeAllButton = nullptr;

#pragma endregion UI_WIDGETS
};