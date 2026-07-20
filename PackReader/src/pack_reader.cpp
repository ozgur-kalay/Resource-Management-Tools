#include "pack_reader.hpp"
#include <iostream>
#include <fstream>
#include "res_pack_signature.hpp"


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

    if (!_is_valid_pack_file(file))
    {
        std::cout << "File is NOT a RES PACK file!\n";
        file.close();
        return;
    }

    std::cout << "File is a VALID RES PACK file!\n";

    file.close();
}


bool PackReader::_is_valid_pack_file(std::ifstream &file)
{
    bool output = true;
    ResPackSignature signature;
    
    char sign_buffer[SIGNATURE_LENGTH + 1] = {};
    file.read(sign_buffer, 8);
    sign_buffer[SIGNATURE_LENGTH] = '\0';

    std::cout << "Checking File Signature: signature on file = " << sign_buffer <<  "\n" ;


    for (int i = 0; i < SIGNATURE_LENGTH; i++)
    {
        if (sign_buffer[i] != SIGNATURE[i])
        {
            output = false;
            std::cout << "characters dont match = " << SIGNATURE[i] << '\n';
        }
    }
    
    return output;
}