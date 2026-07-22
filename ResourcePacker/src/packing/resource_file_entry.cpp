#include "packing/resource_file_entry.hpp"

ResourceFileEntry::ResourceFileEntry(wxString root_dir_name, std::filesystem::path file_path, PackingParameters* pack_params)
{
    this->m_pack_params = pack_params;

    if (root_dir_name.IsEmpty())
    {
        m_root_dir_name = file_path.filename().string();
    } else{
        m_root_dir_name = root_dir_name;
    }
    m_resource_name = file_path.filename().string();
    m_access_name = _get_access_name(file_path); // If its a single file added, it will use its resource name as the access path.
    m_in_path = _get_formated_path(file_path).string();
    m_out_path = _get_out_path(file_path);

    m_data_in_size = std::filesystem::file_size(file_path);
    m_data_in_size_str = wxString::Format("%lu bytes", m_data_in_size);

    m_data_out_size = std::filesystem::file_size(file_path);
    m_data_out_size_str = wxString::Format("%lu bytes", m_data_out_size);

    m_access_name_len = m_access_name.length();
    m_resource_type = Enums::ResType::UNKNOWN;
    m_data_offset = 0;
}

void ResourceFileEntry::SetIdx(unsigned int idx)
{
    m_idx = idx;
}

wxString ResourceFileEntry::_get_access_name(std::filesystem::path file_path)
{
    wxString out;

    switch (m_pack_params->access_name_choice)
    {
        case Enums::AccessNameChoices::RELATIVE_TO_ROOT:
            out = _get_root_relative_access_path(m_root_dir_name, wxString(file_path.string()));
            break;
        case Enums::AccessNameChoices::FILE_NAME_ONLY:
            out = wxString::Format("%s", file_path.filename().string());
            break;
        case Enums::AccessNameChoices::FULL_PATH:
            out = wxString::Format("%s", file_path.string());
            break;
    }
    
    std::replace(out.begin(), out.end(),'\\', '/');
    return out;
}

wxString ResourceFileEntry::_get_out_path(std::filesystem::path file_path)
{
    wxString outpath(m_pack_params->pack_output_dir_path + "/");

    wxString _extention = wxString::Format(".%s",m_pack_params->pack_file_extention);

        switch (m_pack_params->packing_choice)
        {
            case Enums::PackingChoices::PACK_SINGLE_FILE:
                outpath.append(m_pack_params->pack_file_name + _extention);
                break;
            case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
                wxString _file_name = file_path.filename().replace_extension("").string();
                wxLogDebug(wxString::Format("ListRow file name only entered = %s", _file_name));
                outpath.append(_file_name + _extention);
                break;
        }

    return outpath;
}

wxString ResourceFileEntry::_get_root_relative_access_path(wxString root_name, wxString file_path)
{
    wxString out = file_path.substr(file_path.find(root_name));

    return out;
}

std::filesystem::path ResourceFileEntry::_get_formated_path(std::filesystem::path &path)
{
    std::string path_str = path.string();
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    std::filesystem::path out_path(path_str);

    return out_path;
}

wxString ResourceFileEntry::GetString(const wxString& title) const
{
    return wxString::Format(
            "ListRow: %s:\n"
            "    idx = %d\n"
            "    resource_name = %s\n"
            "    access_path = %s\n"
            "    in_path = %s\n"
            "    out_path = %s\n"
            "    in_size = %lu\n"
            "    out_size = %lu",
            title, m_idx, m_resource_name, m_access_name, m_in_path, m_out_path, m_data_in_size, m_data_out_size
        );
}

const wxString& ResourceFileEntry::GetRootDir() const {return m_root_dir_name;}
unsigned int ResourceFileEntry::GetIdx() const {return m_idx; }
const wxString& ResourceFileEntry::GetResourceName() const {return m_resource_name;}
const wxString& ResourceFileEntry::GetAccessName() const {return m_access_name; }
const wxString& ResourceFileEntry::GetInPath() const {return m_in_path;}
const wxString& ResourceFileEntry::GetOutPath() const {return m_out_path;}
unsigned long ResourceFileEntry::GetInSize() const {return m_data_in_size;}
const wxString& ResourceFileEntry::GetInSizeStr() const {return m_data_in_size_str;}
unsigned long ResourceFileEntry::GetOutSize() const {return m_data_out_size;}
const wxString& ResourceFileEntry::GetOutSizeStr() const {return m_data_out_size_str;}

// Table Entry info
unsigned int ResourceFileEntry::GetAccessNameLen() const {return m_access_name_len;}
Enums::ResType ResourceFileEntry::GetResType() const {return m_resource_type; }
unsigned long ResourceFileEntry::GetDataOffSet() const { return m_data_offset; }
