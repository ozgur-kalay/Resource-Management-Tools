#ifndef RES_PACKING_COMMON_PACK_ENTRY_HPP
#define RES_PACKING_COMMON_PACK_ENTRY_HPP
#include <cinttypes>
#include <string>

struct ResourceTableEntry
{
   uint16_t access_name_len = 0;
   std::string acces_name = {};
   uint8_t resource_type = 0;
   uint64_t data_offset = 0;
   uint64_t data_size = 0;
};

#endif // RES_PACKING_COMMON_PACK_ENTRY_HPP