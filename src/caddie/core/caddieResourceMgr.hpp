#ifndef CADDIE_CORE_RESOURCE_MGR_H
#define CADDIE_CORE_RESOURCE_MGR_H
#include "caddieLinkList.hpp"
#include "caddieMessage.hpp"
#include "caddieResource.hpp"
#include "types_caddie.hpp"

namespace caddie {

/**
 * @brief Resource manager
 */
class ResourceMgr {
public:
    static ResourceMgr& GetInstance() {
        static ResourceMgr instance;
        return instance;
    }

    // Load file from DVD with local (scene) lifetime
    void* LoadLocalFromDVD(const char* path) { return LoadFromDVD(path, true); }
    // Load file from DVD with static (global) lifetime
    void* LoadStaticFromDVD(const char* path) {
        return LoadFromDVD(path, false);
    }

    // Load and decompress file from DVD with local (scene) lifetime
    void* LoadLocalCompressedFromDVD(const char* path) {
        return LoadCompressedFromDVD(path, true);
    }
    // Load and decompress file from DVD with static (global) lifetime
    void* LoadStaticCompressedFromDVD(const char* path) {
        return LoadCompressedFromDVD(path, false);
    }

    // Load BCMSG from DVD with local (scene) lifetime
    Message* LoadLocalMessage(const char* path) {
        void* bin = LoadLocalFromDVD(path);
        CADDIE_ASSERT(bin != NULL);
        return new Message(bin);
    }

    // Load BCMSG from DVD with static (global) lifetime
    Message* LoadStaticMessage(const char* path) {
        void* bin = LoadStaticFromDVD(path);
        CADDIE_ASSERT(bin != NULL);
        return new Message(bin);
    }

    void ClearStaticCache();
    void ClearSceneCache();

private:
    ResourceMgr();
    virtual ~ResourceMgr();

    void* LoadFromDVD(const char* path, bool local);
    void* LoadCompressedFromDVD(const char* path, bool local);

    bool LoadFromDVDImpl(const char* path, void*& data, u32& fileSize);

    void AddCachedResource(const char* path, u32 fileSize, void* data,
                           bool local);
    const Resource* FindCachedResource(const char* path);

private:
    // Static-lifetime resource cache
    TLinkList<Resource> mStaticCache;
    // Scene-lifetime resource cache
    TLinkList<Resource> mSceneCache;
};

} // namespace caddie

#endif
