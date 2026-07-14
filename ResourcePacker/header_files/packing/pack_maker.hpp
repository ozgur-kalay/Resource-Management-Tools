#ifndef RES_PACKER_PACK_MAKER_HPP
#define RES_PACKER_PACK_MAKER_HPP
#include "pack_parameters.hpp"

// File Structure: 
// Packed File Signature: [1981, 1990, 2013, 2019] 
// [Packed File Signature][(4bytes) Access Name Glosery Size][Access Name Glossery][Data Entries] 
// Data Entry[ 
//              [(4Bytes) End P of entry] 
//              [(1 Byte) Res Type Enum] 
//              [(2Bytes) Access Name Length] 
//              [Access Name] 
//              [Full File Data]] 
//          ]

class PackMaker
{
    public:
        PackMaker();
        void pack(PackParameters& pack_params);
};

#endif // RES_PACKER_PACK_MAKER_HPP