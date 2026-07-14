#include "controls/classes/list_row.hpp"
#include "packing/pack_manager.hpp"


ListRow::ListRow(wxString root_dir_name, std::filesystem::path file_path)
{
    m_root_dir_name = root_dir_name;
    m_resource_name = file_path.filename().string();
    m_access_path = _get_access_path(file_path); // If its a single file added, it will use its resource name as the access path.
    m_in_path = _get_formated_path(file_path).string();
    m_out_path = _get_out_path(file_path);
    m_in_size = std::filesystem::file_size(file_path);
    m_in_size_str = wxString::Format("%lu bytes", m_in_size);
    m_out_size = std::filesystem::file_size(file_path);
    m_out_size_str = wxString::Format("%lu bytes", m_out_size);
}

void ListRow::SetIdx(unsigned int idx)
{
    m_idx = idx;
}

wxString ListRow::_get_access_path(std::filesystem::path file_path)
{
    wxString out;

    switch (PackManager::GetPackParams().access_name_choice)
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

wxString ListRow::_get_out_path(std::filesystem::path file_path)
{
    wxString outpath(PackManager::GetPackParams().pack_output_dir_path + "/");

    wxString _extention = wxString::Format(".%s",PackManager::GetPackParams().pack_file_extention);

        switch (PackManager::GetPackParams().packing_choice)
        {
            case Enums::PackingChoices::PACK_SINGLE_FILE:
                outpath.append(PackManager::GetPackParams().pack_file_name + _extention);
                break;
            case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
                wxString _file_name = file_path.filename().replace_extension("").string();
                wxLogDebug(wxString::Format("ListRow file name only entered = %s", _file_name));
                outpath.append(_file_name + _extention);
                break;
        }

    return outpath;
}

wxString ListRow::_get_root_relative_access_path(wxString root_name, wxString file_path)
{
    wxString out = file_path.substr(file_path.find(root_name));

    return out;
}

std::filesystem::path ListRow::_get_formated_path(std::filesystem::path &path)
{
    std::string path_str = path.string();
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    std::filesystem::path out_path(path_str);

    return out_path;
}

wxString ListRow::GetString(const wxString& title) const
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
            title, m_idx, m_resource_name, m_access_path, m_in_path, m_out_path, m_in_size, m_out_size
        );
}

wxString ListRow::GetRootDir() const {return m_root_dir_name;}
unsigned int ListRow::GetIdx() const {return m_idx; }
wxString ListRow::GetResourceName() const {return m_resource_name;}
wxString ListRow::GetAccessPath() const {return m_access_path; }
wxString ListRow::GetInPath() const {return m_in_path;}
wxString ListRow::GetOutPath() const {return m_out_path;}
unsigned long ListRow::GetInSize() const {return m_in_size;}
wxString ListRow::GetInSizeStr() const {return m_in_size_str;}
unsigned long ListRow::GetOutSize() const {return m_out_size;}
wxString ListRow::GetOutSizeStr() const {return m_out_size_str;}
