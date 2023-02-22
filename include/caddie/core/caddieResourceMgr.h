#ifndef CADDIE_CORE_RESOURCE_MGR_H
#define CADDIE_CORE_RESOURCE_MGR_H
#include "caddieLinkList.h"
#include "caddieResource.h"
#include "types_caddie.h"

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
    // Load file from DVD with global (static) lifetime
    void* LoadStaticFromDVD(const char* path) {
        return LoadFromDVD(path, false);
    }

    // Load and decompress file from DVD with local (scene) lifetime
    void* LoadLocalCompressedFromDVD(const char* path) {
        return LoadCompressedFromDVD(path, true);
    }
    // Load and decompress file from DVD with global (static) lifetime
    void* LoadStaticCompressedFromDVD(const char* path) {
        return LoadCompressedFromDVD(path, false);
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
