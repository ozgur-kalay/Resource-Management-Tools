// reader_test.cpp
#include <iostream>
#include "pack_reader.hpp"


int main()
{
    PackReader pr;
    pr.open_pack("F:/Projects/Cpp/Tools/Resource-Management-Tools/AssetsPacked/resources.pack");
    
    std::cout << "Hello from Reader Test\n";
    return 0;
}