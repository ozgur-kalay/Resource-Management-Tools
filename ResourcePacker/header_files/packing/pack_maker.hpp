#ifndef RES_PACKER_PACK_MAKER_HPP
#define RES_PACKER_PACK_MAKER_HPP
#include "packing_parameters.hpp"
#include "packing_data.hpp"
#include <fstream>

// File Structure: 
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
class PackMaker
{
    // Members
    private:
        PackingParameters& m_packing_params;
        PackingData& m_packing_data;

    public:
        PackMaker(PackingParameters& pack_params, PackingData& m_packing_data);
        ~PackMaker();

        void pack();

        // Packed File Signature: [1981, 1990, 2013, 2019]
        const uint16_t RESPACK_SIGNATURE[4] = {1981, 1990, 2013, 2019}; // Testing siganture
    
    // Packing Options
    private:
        void _pack_single_file();
        void _pack_individual_files();
    
    // Helpers
    private:
        void _set_signature(std::fstream &file);
        void _set_resource_count(std::fstream &file);
        void _set_resource_file_entry_table(std::fstream &file);
        
};

#endif // RES_PACKER_PACK_MAKER_HPP