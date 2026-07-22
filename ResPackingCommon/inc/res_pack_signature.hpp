#pragma once
#include <string>

#define SIGNATURE "OZGRPACK"

class ResPackSignature
{
    const std::string m_signature = SIGNATURE;
    public:
        const std::string& get_std_str();
        const char* get_c_str();
        bool is_valid(const char* match);
};