#include "caddieResourceMgr.hpp"

#include <cstring>
#include <egg/core.h>
#include <revolution/OS.h>

namespace caddie {

ResourceMgr::ResourceMgr() {}

ResourceMgr::~ResourceMgr() {}

/**
 * @brief Add resource to cache
 *
 * @param path File path
 * @param fileSize File size
 * @param data File data
 * @param heap Parent heap
 */
void ResourceMgr::AddCachedResource(const char* path, u32 fileSize, void* data,
                                    EGG::Heap* heap) {
    CADDIE_ASSERT(path != NULL);
    CADDIE_ASSERT(data != NULL);
    CADDIE_ASSERT(heap != NULL);

    mResCache.Append(new (heap) Resource(path, fileSize, data));
}

/**
 * @brief Remove resource from cache
 * @note Does not free memory, the disposer will do that
 * @param res Resource
 */
void ResourceMgr::RemoveCachedResource(const Resource* res) {
    CADDIE_ASSERT(res != NULL);

    for (TLinkList<Resource>::Iterator it = mResCache.Begin();
         it != mResCache.End(); it++) {
        if (&*it == res) {
            mResCache.Remove(it);
        }
    }
}

/**
 * @brief Check scene/static cache for a specific resource
 *
 * @param path Path
 * @return Resource
 */
const Resource* ResourceMgr::FindCachedResource(const char* path) {
    for (TLinkList<Resource>::Iterator it = mResCache.Begin();
         it != mResCache.End(); it++) {
        if (strcmp(it->GetPath(), path) == 0) {
            return &*it;
        }
    }

    return NULL;
}

/**
 * @brief Load file from DVD
 *
 * @param path File path
 * @param[out] dataOut File data
 * @param[out] sizeOut File size
 * @return Whether the resource was cached
 */
bool ResourceMgr::LoadFromDVDImpl(const char* path, void*& dataOut,
                                  u32& sizeOut) {
    // Use resource cache if possible
    const Resource* cached = FindCachedResource(path);
    if (cached != NULL) {
        dataOut = cached->GetData();
        sizeOut = cached->GetSize();
        return true;
    }

    // Load as new resource
    dataOut = EGG::DvdRipper::loadToMainRAM(
        path, NULL, MemoryMgr::GetInstance().GetSystemHeap(),
        EGG::DvdRipper::ALLOC_DIR_TOP, 0, NULL, &sizeOut);

    CADDIE_WARN_EX(dataOut == NULL, "Failed to load DVD file: %s", path);

    // Not cached
    return false;
}

/**
 * @brief Load file from DVD
 *
 * @param path File path
 * @param heap Parent heap (defaults to static heap)
 * @return void* File data
 */
void* ResourceMgr::LoadFromDVD(const char* path, EGG::Heap* heap) {
    void* data;
    u32 size;

    const bool cached = LoadFromDVDImpl(path, data, size);

    // Add to resource cache
    if (!cached && data != NULL) {
        AddCachedResource(path, size, data, heap);
    }

    return data;
}

/**
 * @brief Load and decompress file from DVD
 *
 * @param path File path
 * @param heap Parent heap (defaults to static heap)
 * @return void* File data (decompressed)
 */
void* ResourceMgr::LoadCompressedFromDVD(const char* path, EGG::Heap* heap) {
    void* data;
    u32 size;

    const bool cached = LoadFromDVDImpl(path, data, size);

    if (!cached && data != NULL) {
        // Attempt to decompress file
        if (EGG::Decomp::checkCompressed(static_cast<u8*>(data))) {
            // Do decompression
            const u32 expandSize =
                EGG::Decomp::getExpandSize(static_cast<u8*>(data));
            u8* decompBuffer = new u8[expandSize];
            EGG::Decomp::decode(static_cast<u8*>(data), decompBuffer);

            // Free compressed buffer
            delete data;

            // Add to resource cache
            AddCachedResource(path, expandSize, decompBuffer, heap);
            return decompBuffer;
        }
    }

    return data;
}

} // namespace caddie
