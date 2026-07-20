#include "packing/pack_maker.hpp"
#include "wx/log.h"
#include "enums.hpp"
#include "res_pack_signature.hpp"


PackMaker::PackMaker(){}

void PackMaker::pack(PackingParameters& pack_params)
{
    wxLogDebug("PackMaker::pack() START:");

    switch (pack_params.packing_choice)
    {
        case Enums::PackingChoices::PACK_SINGLE_FILE:
            _pack_single_file(pack_params);
            break;
        case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
            _pack_individual_files(pack_params);
            break;
    }

    wxLogDebug("PackMaker::pack() END:");
}

void PackMaker::_pack_single_file(PackingParameters& pack_params)
{
    std::string output_path(pack_params.pack_output_dir_path + "/" + pack_params.pack_file_name + "." + pack_params.pack_file_extention);
    std::fstream file(output_path, std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        wxLogDebug("PackMaker:: Could not open file = %s", output_path);
        return;
    } else{
        wxLogDebug("PackMaker:: File Opened.");
    }

    // Packing Process
    _set_signature(file);
    _set_resource_count(file, pack_params);

    wxLogDebug("PackMaker::Packing single file, output file path = %s", output_path);

    file.close();
}

void PackMaker::_pack_individual_files(PackingParameters& pack_params)
{
    wxLogDebug("PackMaker::Packing individual files");
}

void PackMaker::_set_signature(std::fstream &file)
{
    file.seekp(0, std::ios::beg);    
    ResPackSignature signature;
    file.write(signature.get_c_str(), SIGNATURE_LENGTH);
}

void PackMaker::_set_resource_count(std::fstream &file, PackingParameters& pack_params)
{
    
}