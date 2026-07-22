#pragma once
#include <fstream>
#include <array>
#include <initializer_list>
// Notes: Although Enums are not needed to load the data Enums are used to increase the robustness of 

namespace Enums
{
    enum class ResType
    {
        UNKNOWN,

        // Images
        PNG, JPG, BMP, TGA, WEBP,

        // Audio
        WAV, MP3, OGG, FLAC,

        // Models
        OBJ, FBX, GLTF, GLB,

        // Fonts
        TTF, OTF,

        // Shaders
        GLSL, HLSL, SPIRV,

        // Data
        JSON, XML, CSV, TXT,

        // Video
        MP4, WEBM
    };


    inline ResType GetType(std::ifstream& file)
    {
        if (!file.is_open()) return ResType::UNKNOWN;

        std::array<unsigned char, 32> data{};
        const std::streampos position = file.tellg();

        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(data.data()), data.size());
        const std::streamsize bytes_read = file.gcount();

        file.clear();
        file.seekg(position);

        auto matches = [&](std::initializer_list<unsigned char> signature, std::size_t offset = 0)
        {
            if (offset + signature.size() > static_cast<std::size_t>(bytes_read)) return false;

            std::size_t i = offset;
            for (unsigned char byte : signature)
                if (data[i++] != byte) return false;

            return true;
        };

        // Images
        if (matches({0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A})) return ResType::PNG;
        if (matches({0xFF, 0xD8, 0xFF})) return ResType::JPG;
        if (matches({'B', 'M'})) return ResType::BMP;
        if (matches({'R', 'I', 'F', 'F'}) && matches({'W', 'E', 'B', 'P'}, 8)) return ResType::WEBP;

        // Audio
        if (matches({'R', 'I', 'F', 'F'}) && matches({'W', 'A', 'V', 'E'}, 8)) return ResType::WAV;
        if (matches({'I', 'D', '3'}) || (bytes_read >= 2 && data[0] == 0xFF && (data[1] & 0xE0) == 0xE0)) return ResType::MP3;
        if (matches({'O', 'g', 'g', 'S'})) return ResType::OGG;
        if (matches({'f', 'L', 'a', 'C'})) return ResType::FLAC;

        // Models
        if (matches({'K', 'a', 'y', 'd', 'a', 'r', 'a', ' ', 'F', 'B', 'X'})) return ResType::FBX;
        if (matches({'g', 'l', 'T', 'F'})) return ResType::GLB;

        // Fonts
        if (matches({0x00, 0x01, 0x00, 0x00}) || matches({'t', 'r', 'u', 'e'})) return ResType::TTF;
        if (matches({'O', 'T', 'T', 'O'})) return ResType::OTF;

        // Shaders
        if (matches({0x03, 0x02, 0x23, 0x07}) || matches({0x07, 0x23, 0x02, 0x03})) return ResType::SPIRV;

        // Video
        if (matches({'f', 't', 'y', 'p'}, 4)) return ResType::MP4;
        if (matches({0x1A, 0x45, 0xDF, 0xA3})) return ResType::WEBM;

        return ResType::UNKNOWN;
    }
}