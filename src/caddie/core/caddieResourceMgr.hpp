#ifndef CADDIE_CORE_RESOURCE_MGR_H
#define CADDIE_CORE_RESOURCE_MGR_H
#include "caddieLinkList.hpp"
#include "caddieMemoryMgr.hpp"
#include "caddieMessage.hpp"
#include "caddieResource.hpp"
#include "types_caddie.hpp"

namespace caddie {

/**
 * @brief Resource manager
 */
class ResourceMgr {
    friend class Resource;

public:
    static ResourceMgr& GetInstance() {
        static ResourceMgr instance;
        return instance;
    }

    // Load file from DVD
    void*
    LoadFromDVD(const char* path,
                EGG::Heap* heap = MemoryMgr::GetInstance().GetStaticHeap());

    // Load and decompress file from DVD
    void* LoadCompressedFromDVD(
        const char* path,
        EGG::Heap* heap = MemoryMgr::GetInstance().GetStaticHeap());

    // Load binary message (BCMSG) from DVD
    Message*
    LoadMessage(const char* path,
                EGG::Heap* heap = MemoryMgr::GetInstance().GetStaticHeap()) {
        void* bin = LoadFromDVD(path, heap);
        CADDIE_ASSERT(bin != NULL);
        return new Message(bin);
    }

private:
    ResourceMgr();
    virtual ~ResourceMgr();

    bool LoadFromDVDImpl(const char* path, void*& data, u32& fileSize);

    void AddCachedResource(const char* path, u32 fileSize, void* data,
                           EGG::Heap* heap);
    void RemoveCachedResource(const Resource* res);
    const Resource* FindCachedResource(const char* path);

private:
    // Resource cache
    TLinkList<Resource> mResCache;
};

} // namespace caddie

#endif
