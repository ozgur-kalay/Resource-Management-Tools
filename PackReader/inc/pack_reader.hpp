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
        bool _is_valid_pack_file(std::ifstream &file);
        std::filesystem::path res_pack_file_path;
};