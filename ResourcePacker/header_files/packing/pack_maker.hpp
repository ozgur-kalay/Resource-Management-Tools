#ifndef RES_PACKER_PACK_MAKER_HPP
#define RES_PACKER_PACK_MAKER_HPP
#include "packing_parameters.hpp"
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
    public:
        PackMaker();
        void pack(PackingParameters& pack_params);

        // Packed File Signature: [1981, 1990, 2013, 2019]
        const uint16_t RESPACK_SIGNATURE[4] = {1981, 1990, 2013, 2019}; // Testing siganture
    
    // Packing Options
    private:
        void _pack_single_file(PackingParameters& pack_params);
        void _pack_individual_files(PackingParameters& pack_params);
    
    // Helpers
    private:
        void _set_signature(std::fstream &file);
        void _set_resource_count(std::fstream &file, PackingParameters& pack_params);
        
};

#endif // RES_PACKER_PACK_MAKER_HPP