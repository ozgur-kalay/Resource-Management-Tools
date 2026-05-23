#include "resource_manager.hpp"
#include <cstddef>
#include <algorithm>
#include <functional>


#pragma region RESOURCE_MANAGEMENT

void ResourceManager::AddResource(const ResourceEntry& entry)
{
    m_resources.push_back(entry);
}

bool ResourceManager::RemoveResourceAtIndex(std::size_t index)
{
    if (index >= m_resources.size())
    {
        return false;
    }

    m_resources.erase(
        m_resources.begin() + static_cast<std::ptrdiff_t>(index)
    );

    return true;
}
bool ResourceManager::RemoveResourcesAtIndices(
    const std::vector<long>& indices
)
{
    if (indices.empty())
    {
        return false;
    }

    std::vector<long> sortedIndices = indices;

    std::sort(
        sortedIndices.begin(),
        sortedIndices.end(),
        std::greater<long>()
    );

    bool removedAny = false;

    for (long index : sortedIndices)
    {
        if (index < 0)
        {
            continue;
        }

        std::size_t resourceIndex = static_cast<std::size_t>(index);

        if (resourceIndex >= m_resources.size())
        {
            continue;
        }

        m_resources.erase(
            m_resources.begin() + static_cast<std::ptrdiff_t>(resourceIndex)
        );

        removedAny = true;
    }

    return removedAny;
}

void ResourceManager::ClearResources()
{
    m_resources.clear();
}

#pragma endregion RESOURCE_MANAGEMENT

#pragma region RESOURCE_ACCESS

const std::vector<ResourceEntry>& ResourceManager::GetResources() const
{
    return m_resources;
}

std::size_t ResourceManager::GetResourceCount() const
{
    return m_resources.size();
}

std::uintmax_t ResourceManager::GetTotalSizeBytes() const
{
    std::uintmax_t totalSize = 0;

    for (const ResourceEntry& resource : m_resources)
    {
        totalSize += resource.fileSizeBytes;
    }

    return totalSize;
}
bool ResourceManager::ContainsSourcePath(const wxString& sourcePath) const
{
    for (const ResourceEntry& resource : m_resources)
    {
        if (resource.sourcePath == sourcePath)
        {
            return true;
        }
    }

    return false;
}
#pragma endregion RESOURCE_ACCESS