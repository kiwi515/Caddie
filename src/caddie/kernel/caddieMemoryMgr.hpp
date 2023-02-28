#ifndef CADDIE_KERNEL_MEMORY_MGR_H
#define CADDIE_KERNEL_MEMORY_MGR_H
#include "caddieHashMap.hpp"
#include "types_caddie.hpp"

#include <egg/core.h>

namespace caddie {

/**
 * @brief Caddie memory manager
 */
class MemoryMgr {
public:
    static MemoryMgr& GetInstance() {
        static MemoryMgr instance;
        return instance;
    }

    void CreateSceneHeap();
    void DestroySceneHeap();

    void* Alloc(size_t size, int align);
    void* Alloc(size_t size, int align, EGG::Heap* heap);

    void Free(void* block);
    void Free(void* block, EGG::Heap* heap);

    u32 GetFreeSize() { return GetStaticFreeSize() + GetSceneFreeSize(); }

    u32 GetStaticFreeSize() {
        CADDIE_ASSERT(mStaticHeap != NULL);
        return mStaticHeap->getAllocatableSize(4);
    }

    u32 GetSceneFreeSize() {
        return mSceneHeap != NULL ? mSceneHeap->getAllocatableSize(4) : 0;
    }

    EGG::ExpHeap* GetStaticHeap() const { return mStaticHeap; }
    EGG::ExpHeap* GetSceneHeap() const { return mStaticHeap; }

private:
    MemoryMgr();
    virtual ~MemoryMgr();

    void CreateStaticHeap();

private:
    // Heap with static lifetime
    EGG::ExpHeap* mStaticHeap;
    // Heap with scene lifetime
    EGG::ExpHeap* mSceneHeap;

    static const u32 scStaticHeapSize = 64 * 1024; // 64KB
    static const u32 scSceneHeapSize = 16 * 1024;  // 4KB
};

} // namespace caddie

#endif
