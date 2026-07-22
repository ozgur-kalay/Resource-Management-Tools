#pragma once
#include <filesystem>
#include "wx/wx.h"
#include "null_idx.hpp"
#include "resource_types.hpp"
#include "packing_parameters.hpp"

class ResourceFileEntry
{
    public:
        ResourceFileEntry(wxString root_dir_name, std::filesystem::path file_path, PackingParameters* pack_params);
        
        wxString GetString(const wxString& title) const;
    private:
        PackingParameters* m_pack_params = nullptr;
    // Packing Members
    private:
        wxString m_root_dir_name = {};
        unsigned int m_idx = null_idx;
        wxString m_resource_name = {};
        wxString m_access_name = {};
        wxString m_in_path = {};
        wxString m_out_path = {};
        unsigned long m_data_in_size = 0;
        wxString m_data_in_size_str;
        unsigned long m_data_out_size = 0;
        wxString m_data_out_size_str = {};

        uint16_t m_access_name_len = 0;
        Enums::ResType m_resource_type = Enums::ResType::UNKNOWN;
        unsigned long m_data_offset = 0;

    // Member Setters
    public:
        void SetIdx(unsigned int idx);
    // Member Getters
    public:
        const wxString& GetRootDir() const;
        unsigned int GetIdx() const;
        const wxString& GetResourceName() const;
        const wxString& GetAccessName() const;
        const wxString& GetInPath() const;
        const wxString& GetOutPath() const;
        unsigned long GetInSize() const;
        const wxString& GetInSizeStr() const;
        unsigned long GetOutSize() const;
        const wxString& GetOutSizeStr() const;
        
        // Table Entry info
        unsigned int GetAccessNameLen() const;
        Enums::ResType GetResType() const;
        unsigned long GetDataOffSet() const;

    // Helpers
    private:
        wxString _get_out_path(std::filesystem::path file_path);
        wxString _get_access_name(std::filesystem::path file_path);
        wxString _get_root_relative_access_path(wxString root_name, wxString file_path);
        std::filesystem::path _get_formated_path(std::filesystem::path &path);
};