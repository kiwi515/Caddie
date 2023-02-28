#ifndef CADDIE_KERNEL_MEM_MGR_H
#define CADDIE_KERNEL_MEM_MGR_H
#include "types_caddie.hpp"

#include <egg/core.h>

namespace caddie {

/**
 * @brief Caddie memory manager
 * @details Manages child of main game heap
 */
class MemManager {
public:
    static void Initialize();

    static void* Alloc(size_t size, int align) {
        CADDIE_ASSERT(sGameHeap != NULL);
        return sGameHeap->alloc(size, align);
    }

    static void Free(void* block) {
        CADDIE_ASSERT(sGameHeap != NULL);
        sGameHeap->free(block);
    }

    static u32 GetFreeSize() {
        CADDIE_ASSERT(sGameHeap != NULL);
        return sGameHeap->getAllocatableSize(4);
    }

    static EGG::ExpHeap* GetGameHeap() { return sGameHeap; }

private:
    MemManager() {}
    virtual ~MemManager() {}

    //! @brief Caddie main heap
    static EGG::ExpHeap* sGameHeap;
    //! @brief Caddie main heap size (configurable)
    static const u32 scHeapSize;
};

} // namespace caddie

inline void* operator new(size_t size) {
    return caddie::MemManager::Alloc(size, 4);
}

inline void* operator new[](size_t size) {
    return caddie::MemManager::Alloc(size, 4);
}

inline void operator delete(void* block) { caddie::MemManager::Free(block); }

inline void operator delete[](void* block) { caddie::MemManager::Free(block); }

#endif
