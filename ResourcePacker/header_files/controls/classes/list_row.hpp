#pragma once
#include <filesystem>
#include "wx/wx.h"
#include "null_idx.hpp"

class ListRow
{
    public:
        ListRow(wxString root_dir_name, std::filesystem::path file_path);
        wxString GetString(const wxString& title) const;
    
    // Members
    private:
        wxString m_root_dir_name;
        unsigned int m_idx = null_idx;
        wxString m_resource_name;
        wxString m_access_path;
        wxString m_in_path;
        wxString m_out_path;
        unsigned long m_in_size = 0;
        wxString m_in_size_str;
        unsigned long m_out_size = 0;
        wxString m_out_size_str;

    // Member Setters
    public:
        void SetIdx(unsigned int idx);
    // Member Getters
    public:
        wxString GetRootDir() const;
        unsigned int GetIdx() const;
        wxString GetResourceName() const;
        wxString GetAccessPath() const;
        wxString GetInPath() const;
        wxString GetOutPath() const;
        unsigned long GetInSize() const;
        wxString GetInSizeStr() const;
        unsigned long GetOutSize() const;
        wxString GetOutSizeStr() const;

    // Helpers
    private:
        wxString _get_out_path(std::filesystem::path file_path);
        wxString _get_access_path(std::filesystem::path file_path);
        wxString _get_root_relative_access_path(wxString root_name, wxString file_path);
};