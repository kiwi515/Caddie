#ifndef CADDIE_KERNEL_MEM_MGR_H
#define CADDIE_KERNEL_MEM_MGR_H
#include "types_caddie.h"

#include <egg/core.h>

namespace caddie {

/**
 * @brief Caddie memory manager
 * @details Manages child of main game heap
 */
class MemManager {
public:
    static void Initialize();

    static void* Alloc(u32 size, s32 align) {
        CADDIE_ASSERT(sHeap != NULL);
        return sHeap->alloc(size, align);
    }

    static void Free(void* block) {
        CADDIE_ASSERT(sHeap != NULL);
        sHeap->free(block);
    }

    static u32 GetFreeSize() {
        CADDIE_ASSERT(sHeap != NULL);
        return sHeap->getAllocatableSize(4);
    }

private:
    MemManager() {}
    ~MemManager() {}

    //! @brief Caddie main heap
    static EGG::ExpHeap* sHeap;
    //! @brief Caddie main heap size (configurable)
    static u32 sHeapSize;
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
