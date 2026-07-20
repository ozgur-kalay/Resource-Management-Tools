#include "res_pack_signature.hpp"
#include <iostream>

const std::string& ResPackSignature::get_std_str()
{
    return m_signature;
}

const char* ResPackSignature::get_c_str()
{
    return m_signature.data();
}

bool ResPackSignature::is_valid(const char* match)
{
    return SIGNATURE == match;
}
