#include "pack_reader.hpp"
#include <iostream>
#include <fstream>
#include "res_pack_signature.hpp"
#include "pack_meta_lengths.hpp"
#include <vector>
#include "resource_table_entry.hpp"


PackReader::PackReader(){}
PackReader::~PackReader()
{
    res_pack_file_path.clear();
}


void PackReader::open_pack(const char* _pack_path)
{
    res_pack_file_path = _pack_path;
    std::cout << "PackReader::open_pack:: OPENING: " << res_pack_file_path.string() << '\n';

    std::ifstream file(res_pack_file_path, std::ios::binary | std::ios::beg);
    

    if (!file.is_open())
    {
        std::cout << "COULD NOT OPEN FILE" << '\n';
        return;
    }

    // _file_read_test(file);
    // return;

    if (!_is_valid_pack_file(file))
    {
        std::cout << "File is NOT a RES PACK file!\n";
        file.close();
        return;
    }

    std::cout << "File is a VALID RES PACK file!\n";

    m_res_count = _get_res_count(file);

    if (m_res_count <= 0)
    {
        std::cout << "File Empty. No Resources to unpack.\n";
        return;
    }

    _get_resource_table(file);


    file.close();
}


bool PackReader::_is_valid_pack_file(std::ifstream &file)
{
    bool output = true;
    ResPackSignature signature;
    
    char sign_buffer[SIGNATURE_META_LEN + 1] = {};
    file.read(sign_buffer, 8);
    sign_buffer[SIGNATURE_META_LEN] = '\0';

    std::cout << "Checking File Signature: signature on file = " << sign_buffer <<  "\n" ;


    for (int i = 0; i < SIGNATURE_META_LEN; i++)
    {
        if (sign_buffer[i] != SIGNATURE[i])
        {
            output = false;
            std::cout << "characters dont match = " << SIGNATURE[i] << '\n';
        }
    }
    
    return output;
}

int PackReader::_get_res_count(std::ifstream &file)
{
    file.seekg(8, std::ios::beg);

    int buffer = 0;

    file.read((char*)&buffer, sizeof(int));

    std::cout << "PackReader::_get_res_count = " << buffer << '\n';

    return buffer;
}

void PackReader::_get_resource_table(std::ifstream &file)
{
    std::cout << "PackReader::_get_resource_table()" << '\n';
    file.seekg(RESOURCE_TABLE_START, std::ios::beg);

    std::vector<ResourceTableEntry> table_enteries;

    for (int i =0; i < m_res_count; i++)
    {
        ResourceTableEntry t_entry;

        // Length
        file.read((char*)&t_entry.access_name_len, sizeof(t_entry.access_name_len));

        // Access Name
        t_entry.acces_name.resize(t_entry.access_name_len);
        file.read(t_entry.acces_name.data(), t_entry.access_name_len);

        // // Resource Type
        // file.read((char*)&t_entry.resource_type, sizeof(t_entry.resource_type));

        // // Data Offset
        // file.read((char*)&t_entry.data_offset, sizeof(t_entry.data_offset));

        // // Data Size
        // file.read((char*)&t_entry.data_size, sizeof(t_entry.data_size));

        // table_enteries.push_back(t_entry);

        std::cout << "ResEntry: access_name = " << t_entry.acces_name << '\n';
    }
    
}



void PackReader::_file_read_test(std::ifstream &file)
{
    
}