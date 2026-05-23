#pragma once

#include "resource_entry.hpp"

#include <vector>

class ResourceManager
{
public:
#pragma region RESOURCE_MANAGEMENT

    void AddResource(const ResourceEntry& entry);
    bool RemoveResourceAtIndex(std::size_t index);
    bool RemoveResourcesAtIndices(const std::vector<long>& indices);

    void ClearResources();

#pragma endregion RESOURCE_MANAGEMENT

#pragma region RESOURCE_ACCESS

    const std::vector<ResourceEntry>& GetResources() const;

    std::size_t GetResourceCount() const;

    std::uintmax_t GetTotalSizeBytes() const;

    bool ContainsSourcePath(const wxString& sourcePath) const;

#pragma endregion RESOURCE_ACCESS

private:
#pragma region RESOURCE_STORAGE

    std::vector<ResourceEntry> m_resources;

#pragma endregion RESOURCE_STORAGE
};