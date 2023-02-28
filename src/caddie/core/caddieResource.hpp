#ifndef CADDIE_CORE_RESOURCE_H
#define CADDIE_CORE_RESOURCE_H
#include "caddieLinkList.hpp"
#include "types_caddie.hpp"

#include <egg/core.h>

namespace caddie {

/**
 * @brief Wrapper for resources loaded into memory
 * @note Garbage collected when parent heap is destroyed
 */
class Resource : public EGG::Disposer {
public:
    static u32 GetNodeOffset() { return offsetof(Resource, mNode); }

    Resource(const char* path, u32 size, void* data)
        : mPath(path), mSize(size), mData(static_cast<u8*>(data)) {
        CADDIE_ASSERT(mPath != NULL);
        CADDIE_ASSERT(mData != NULL);
    }

    virtual ~Resource() { delete mData; }

    const char* GetPath() const { return mPath; }
    u32 GetSize() const { return mSize; }
    void* GetData() const { return mData; }

private:
    TLinkListNode mNode;

    // File path
    const char* mPath;
    // File size
    u32 mSize;
    // File data
    u8* mData;
};

} // namespace caddie

#endif