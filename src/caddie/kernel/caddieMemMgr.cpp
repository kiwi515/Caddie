#include "caddieMemMgr.h"

namespace caddie {

/**
 * @brief Initialize Caddie main heap
 */
void MemManager::Initialize() {
    CADDIE_ASSERT_EX(sGameHeap == NULL, "MemManager already initialized!");

    // Child of sAllocatableHeap
    sGameHeap = EGG::ExpHeap::create(scHeapSize, NULL, 0);
    CADDIE_ASSERT_EX(sGameHeap != NULL, "Main game heap creation failed!!!");
}

EGG::ExpHeap* MemManager::sGameHeap = NULL;
const u32 MemManager::scHeapSize = 64 * 1024; // 64KB

} // namespace caddie
