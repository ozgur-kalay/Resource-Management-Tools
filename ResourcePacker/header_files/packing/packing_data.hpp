#pragma once
#include <vector>
#include "resource_file_entry.hpp"


struct PackingData
{
    std::vector<ResourceFileEntry> resource_file_entries {};

    std::vector<char> data_buffer = {};

    unsigned int get_resource_count() {return resource_file_entries.size();}
};