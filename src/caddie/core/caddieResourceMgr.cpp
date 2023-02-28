#include "caddieResourceMgr.hpp"

#include <RevoSDK/OS.h>
#include <cstring>
#include <egg/core.h>

namespace caddie {

ResourceMgr::ResourceMgr() {}

ResourceMgr::~ResourceMgr() {
    ClearStaticCache();
    ClearSceneCache();
}

/**
 * @brief Add resource to cache
 *
 * @param path File path
 * @param fileSize File size
 * @param data File data
 * @param local Local scope
 */
void ResourceMgr::AddCachedResource(const char* path, u32 fileSize, void* data,
                                    bool local) {
    CADDIE_ASSERT(path != NULL);
    CADDIE_ASSERT(data != NULL);

    if (local) {
        mSceneCache.Append(new Resource(path, fileSize, data));
    } else {
        mStaticCache.Append(new Resource(path, fileSize, data));
    }
}

/**
 * @brief Check scene/static cache for a specific resource
 *
 * @param path Path
 * @return Resource
 */
const Resource* ResourceMgr::FindCachedResource(const char* path) {
    // Static cache
    for (TLinkList<Resource>::Iterator it = mStaticCache.Begin();
         it != mStaticCache.End(); it++) {
        if (strcmp(it->GetPath(), path) == 0) {
            return &*it;
        }
    }

    // Scene cache
    for (TLinkList<Resource>::Iterator it = mSceneCache.Begin();
         it != mSceneCache.End(); it++) {
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
        path, NULL, MemManager::GetGameHeap(), EGG::DvdRipper::ALLOC_DIR_TOP, 0,
        NULL, &sizeOut);

    CADDIE_WARN_EX(dataOut == NULL, "Failed to load DVD file: %s", path);

    // Not cached
    return false;
}

/**
 * @brief Load file from DVD
 *
 * @param path File path
 * @param local Local scope
 * @return void* File data
 */
void* ResourceMgr::LoadFromDVD(const char* path, bool local) {
    void* data;
    u32 size;

    const bool cached = LoadFromDVDImpl(path, data, size);

    // Add to resource cache
    if (!cached && data != NULL) {
        AddCachedResource(path, size, data, local);
    }

    return data;
}

/**
 * @brief Load and decompress file from DVD
 *
 * @param path File path
 * @param local Local scope
 * @return void* File data (decompressed)
 */
void* ResourceMgr::LoadCompressedFromDVD(const char* path, bool local) {
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
            AddCachedResource(path, expandSize, decompBuffer, local);
            return decompBuffer;
        }
    }

    return data;
}

/**
 * @brief Clear static resource cache
 */
void ResourceMgr::ClearStaticCache() {
    TLinkList<Resource>::Iterator it = mStaticCache.Begin();
    for (; it != mStaticCache.End(); it++) {
        delete &*it;
    }
}

/**
 * @brief Clear scene resource cache
 */
void ResourceMgr::ClearSceneCache() {
    TLinkList<Resource>::Iterator it = mSceneCache.Begin();
    for (; it != mSceneCache.End(); it++) {
        delete &*it;
    }
}

} // namespace caddie
