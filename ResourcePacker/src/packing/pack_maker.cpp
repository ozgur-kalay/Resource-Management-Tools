#include "packing/pack_maker.hpp"
#include "wx/log.h"
#include "enums.hpp"
#include "res_pack_signature.hpp"
#include "pack_meta_lengths.hpp"


PackMaker::PackMaker(PackingParameters& packing_params, PackingData& _packing_data) 
    : m_packing_params(packing_params), m_packing_data(_packing_data) {}

PackMaker::~PackMaker() {}

void PackMaker::pack()
{
    wxLogDebug("PackMaker::pack() START:");

    switch (m_packing_params.packing_choice)
    {
        case Enums::PackingChoices::PACK_SINGLE_FILE:
            _pack_single_file();
            break;
        case Enums::PackingChoices::PACK_INDIVIDUAL_FILES:
            _pack_individual_files();
            break;
    }

    wxLogDebug("PackMaker::pack() END:");
}

void PackMaker::_pack_single_file()
{
    std::string output_path(m_packing_params.pack_output_dir_path + "/" + m_packing_params.pack_file_name + "." + m_packing_params.pack_file_extention);
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
    _set_resource_count(file);
    _set_resource_file_entry_table(file);

    wxLogDebug("PackMaker::Packing single file, output file path = %s", output_path);

    file.close();
}

void PackMaker::_pack_individual_files()
{
    wxLogDebug("PackMaker::Packing individual files");
}

void PackMaker::_set_signature(std::fstream &file)
{
    file.seekp(META_BEG, std::ios::beg);    
    ResPackSignature signature;
    file.write(signature.get_c_str(), SIGNATURE_META_LEN);
}

void PackMaker::_set_resource_count(std::fstream &file)
{
    file.seekp(RESOURCE_COUNT_START, std::ios::beg);

    unsigned int count = m_packing_data.get_resource_count();

    file.write((const char*)&count, sizeof(unsigned int));
}

void PackMaker::_set_resource_file_entry_table(std::fstream& file)
{
    std::vector<char> table_buffer;

    for (auto& file_entry : m_packing_data.resource_file_entries)
    {
        uint16_t len = file_entry.GetAccessNameLen();
        std::string name = file_entry.GetAccessName().ToStdString();       

        std::vector<char> entry_buffer;

        entry_buffer.insert(entry_buffer.end(), reinterpret_cast<char*>(&len), reinterpret_cast<char*>(&len) + sizeof(len));
        entry_buffer.insert(entry_buffer.end(), name.begin(), name.end());



        table_buffer.insert(table_buffer.end(), entry_buffer.begin(), entry_buffer.end());
    }

    file.seekp(RESOURCE_TABLE_START, std::ios::beg);
    file.write(table_buffer.data(), table_buffer.size());

}


// Offset 0
// ┌─────────────────────────────────────────────────────────────┐
// │ PACK HEADER                                                 │
// │-------------------------------------------------------------│
// │ Signature            "OZGRPACK" (8 Bytes)                   │
// │ Resource Count       (4 Bytes)                              │
// └─────────────────────────────────────────────────────────────┘

// ┌─────────────────────────────────────────────────────────────┐
// │ RESOURCE TABLE                                              │
// │-------------------------------------------------------------│
// │ Resource Entry 0                                            │
// │                                                             │
// │   Access Name Length    (2 Bytes)                           │
// │   Access Name           (Variable Length)                   │
// │   Resource Type         (1 Byte)                            │
// │   Data Offset           (8 Bytes)                           │
// │   Data Size             (8 Bytes)                           │
// │                                                             │
// │-------------------------------------------------------------│
// │ Resource Entry 1                                            │
// │                                                             │
// │   Access Name Length                                        │
// │   Access Name                                               │
// │   Resource Type                                             │
// │   Data Offset                                               │
// │   Data Size                                                 │
// │                                                             │
// │-------------------------------------------------------------│
// │ ...                                                         │
// └─────────────────────────────────────────────────────────────┘

// ┌─────────────────────────────────────────────────────────────┐
// │ DATA SECTION                                                │
// │-------------------------------------------------------------│
// │ Resource 0 Raw Bytes                                        │
// │ Resource 1 Raw Bytes                                        │
// │ Resource 2 Raw Bytes                                        │
// │ ...                                                         │
// └─────────────────────────────────────────────────────────────┘