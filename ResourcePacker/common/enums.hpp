#ifndef RES_PACKER_ENUMS_HPP
#define RES_PACKER_ENUMS_HPP


namespace Enums
{
    enum class PackingChoices : uint8_t {PACK_SINGLE_FILE, PACK_INDIVIDUAL_FILES};
    enum class ResAccessPathChoices : uint8_t {RELATIVE_TO_ROOT, FULL_PATH, FILE_NAME_ONLY};
}

#endif // RES_PACKER_ENUMS_HPP