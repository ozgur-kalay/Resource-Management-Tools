#include <iostream>
#include <fstream>
#include "raylib.h"
#include <vector>
#include <filesystem>

bool is_buffer_png(char* buffer)
{
    int png_sign[8] = {137, 80, 78, 71, 13, 10, 26, 10};

    for (int i = 0; i < 8;i++)
    {
        int _byte = static_cast<int>(static_cast<unsigned char>(buffer[i]));

        if (png_sign[i] != _byte)
        {
            return false;
        }
    }

    return true;
}

std::string _get_root_relative_access_path(std::string root_name, std::filesystem::path path)
{
    std::string out = path.string().substr(path.string().find(root_name));

    return out;
}

int main()
{
    std::filesystem::recursive_directory_iterator dir_iter("F:/Projects/Cpp/Tools/Resource-Management-Tools/ResourcePacker/test/Assets");

    for (auto entry : dir_iter)
    {
        
        std::cout << "Access Path = " << _get_root_relative_access_path("Assets", entry) << "\n";
        
        //std::cout <<"Parent path : " << entry.path().parent_path().filename().string() << "\n";
        // if (std::filesystem::is_regular_file(entry))
        // {
        //     std::cout << "File Found: " << entry << '\n';
        // }
    }


    return 0;
}

// int main()
// {
//     std::fstream file("F:/Projects/Cpp/ResourcePacker/Assets/player/player-idle-96x96.png", std::ios::binary | std::ios::in);

//     if (!file.is_open())
//     {
//         std::cout << "FILE NOT OPEN\n";
//         return 1;
//     }

//     std::cout << "FILE OPEN\n";

//     file.seekg(0, std::ios::end);
//     std::streamsize file_size = file.tellg();
//     file.seekg(0, std::ios::beg);

//     std::cout << "file_size = " << file_size << '\n';
    
//     char *buffer = new char[file_size];

//     file.read(buffer, file_size);

//     const char* file_type;
//     if (is_buffer_png(buffer))
//     {
//         std::cout << "DATA PNG\n";
//         file_type = ".png";
//     } else
//     {
//         std::cout << "DATA NOT PNG\n";
//     }

//     file.close();

//     std::ofstream new_file("F:/Projects/Cpp/ResourcePacker/Assets/test.png", std::ios::binary);

//     new_file.write(buffer, file_size);

//     new_file.close();

//     std::cout << "\nFile Operation Finished.\n";

//     InitWindow(1920, 1080, "");

//     //Image img = LoadImageFromMemory(file_type, (unsigned char*)buffer, file_size);
//     Texture2D txt = LoadTexture("F:/Projects/Cpp/ResourcePacker/Assets/test.png");

//     while (!WindowShouldClose())
//     {
//         BeginDrawing();
//         ClearBackground(BLACK);

//         DrawTexture(txt, 0, 0, WHITE);

//         EndDrawing();
//     }
    
//     CloseWindow();

//     return 0;
// }