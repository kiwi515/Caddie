#ifndef CADDIE_KERNEL_MEMORY_MGR_H
#define CADDIE_KERNEL_MEMORY_MGR_H
#include "types_caddie.hpp"

#include <RP/RPSystem.h>
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

    void* Alloc(size_t size, int align);
    void* Alloc(size_t size, int align, EGG::Heap* heap);

    void Free(void* block);
    void Free(void* block, EGG::Heap* heap);

    u32 GetFreeSize() { return GetSystemFreeSize() + GetSceneFreeSize(); }

    u32 GetSystemFreeSize() {
        CADDIE_ASSERT(mSystemHeap != NULL);
        return GetSystemHeap()->getAllocatableSize(4);
    }

    u32 GetSceneFreeSize() {
        return GetSceneHeap() != NULL ? GetSceneHeap()->getAllocatableSize(4)
                                      : 0;
    }

    EGG::ExpHeap* GetSystemHeap() const { return mSystemHeap; }

    EGG::ExpHeap* GetSceneHeap() const {
        // Current scene
        RPSysScene* currScene = static_cast<RPSysScene*>(
            RPSysSceneMgr::getInstance().getCurrentScene());

        // Current scene's MEM1 heap
        return currScene != NULL
                   ? static_cast<EGG::ExpHeap*>(currScene->getHeapMem1())
                   : NULL;
    }

private:
    MemoryMgr();
    virtual ~MemoryMgr();

    void Initialize();

private:
    // Heap with static lifetime
    EGG::ExpHeap* mSystemHeap;

    static const u32 scSystemHeapSize = 256 * 1024; // 256KB
};

} // namespace caddie

#endif
