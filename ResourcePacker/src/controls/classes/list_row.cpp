#include "controls/classes/list_row.hpp"
#include "packing/pack_manager.hpp"


ListRow::ListRow(wxString root_dir_name, std::filesystem::path file_path)
{
    m_root_dir_name = root_dir_name;
    m_resource_name = wxString(file_path.filename().string());
    m_access_path = _get_access_path(file_path); // If its a single file added, it will use its resource name as the access path.
    m_in_path = wxString(file_path.string());
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

wxString ListRow::_get_out_path(std::filesystem::path file_path)
{
    PackManager& pack_man = PackManager::GetInstance();
    wxString outpath(pack_man.GetPackData().output_dir_path + "/");

        switch (pack_man.GetPackData().packing_choice)
        {
            case Enums::PackingChoices::PACK_SINGLE_FILE:
                outpath.append(pack_man.GetPackData().pack_file_name);
                break;
            case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
                outpath.append(file_path.filename().string());
                break;
        }

    return outpath;
}

wxString ListRow::_get_access_path(std::filesystem::path file_path)
{
    wxString out;
    switch (PackManager::GetInstance().GetPackData().access_name_choice)
    {
        case Enums::ResAccessPathChoices::RELATIVE_TO_ROOT:
            out = _get_root_relative_access_path(m_root_dir_name, wxString(file_path.string()));
            break;
        case Enums::ResAccessPathChoices::FILE_NAME_ONLY:
            out = wxString::Format("%s", file_path.filename().string());
            break;
        case Enums::ResAccessPathChoices::FULL_PATH:
            out = wxString::Format("%s", file_path.string());
            break;
    }

    return out;
}

wxString ListRow::_get_root_relative_access_path(wxString root_name, wxString file_path)
{
    wxString out = file_path.substr(file_path.find(root_name));

    return out;
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
