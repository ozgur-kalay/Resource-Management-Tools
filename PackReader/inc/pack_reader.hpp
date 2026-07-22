#pragma once
#include <string>
#include <filesystem>

class PackReader
{
    public:
        PackReader();
        ~PackReader();
        void open_pack(const char* _pack_path);
    private:
        std::filesystem::path res_pack_file_path;
        bool _is_valid_pack_file(std::ifstream &file);
        int _get_res_count(std::ifstream &file);

        void _get_resource_table(std::ifstream &file);

        void _file_read_test(std::ifstream &file);

    // Members
    private:
        int m_res_count = 0;
};