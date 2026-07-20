#ifndef RES_PACKER_ENUMS_HPP
#define RES_PACKER_ENUMS_HPP
#include <cinttypes>


namespace Enums
{
    enum class PackingChoices : uint8_t {PACK_SINGLE_FILE, PACK_INDIVIDUAL_FILES};
    enum class AccessNameChoices : uint8_t {RELATIVE_TO_ROOT, FULL_PATH, FILE_NAME_ONLY};
    
    enum class PackReadyFlags : uint8_t {
        NONE = 0,
        HAS_FILE_NAME = 1 << 0,
        HAS_FILE_EXTENTION = 1 << 1,
        HAS_OUTPUT_DIR = 1 << 2, 
        HAS_FILES_TO_PACK = 1 << 3
    };

}

#endif // RES_PACKER_ENUMS_HPP