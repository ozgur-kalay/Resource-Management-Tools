#ifndef RES_PACKER_PACK_MANAGER_HPP
#define RES_PACKER_PACK_MANAGER_HPP
#include "enums.hpp"
#include <vector>

class PackManager
{
    struct FileData
    {
        wxString in_path;
        wxString out_path;
    };
    struct PackData
    {
        Enums::PackingChoices packing_choice;
        wxString pack_file_name;
        wxString output_dir_path;
        Enums::ResAccessPathChoices access_name_choice;

        std::vector<FileData> file_datas;
    };
    
    PackData pack_data;
public:
    static PackManager& GetInstance()
    {
        static PackManager instance;
        return instance;
    }

    PackManager(const PackManager&) = delete;
    PackManager& operator=(const PackManager&) = delete;

    PackData& GetPackData()
    {
        return pack_data;
    }

    void AddPackingChoice(Enums::PackingChoices packing_choice)
    {
        this->pack_data.packing_choice = packing_choice;
    }

    void AddPackFileName(wxString pack_file_name)
    {
        this->pack_data.pack_file_name = pack_file_name;
    }

    void AddOutputDir(wxString output_dir_path)
    {
        this->pack_data.output_dir_path = output_dir_path;
    }

    void AddAccessNameChoice(Enums::ResAccessPathChoices access_name_choice)
    {
        this->pack_data.access_name_choice = access_name_choice;
    }

private:
    PackManager() = default;
};

#endif // RES_PACKER_PACK_MANAGER_HPP