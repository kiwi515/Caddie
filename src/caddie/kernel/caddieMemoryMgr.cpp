#include "caddieMemoryMgr.hpp"

namespace caddie {

/**
 * @brief Initialize Caddie main heap
 */
void MemoryMgr::Initialize() {
    CADDIE_ASSERT_EX(sGameHeap == NULL, "MemoryMgr already initialized!");

    // Child of sAllocatableHeap
    sGameHeap = EGG::ExpHeap::create(scHeapSize, NULL, 0);
    CADDIE_ASSERT_EX(sGameHeap != NULL, "Main game heap creation failed!!!");
}

EGG::ExpHeap* MemoryMgr::sGameHeap = NULL;
const u32 MemoryMgr::scHeapSize = 64 * 1024; // 64KB

} // namespace caddie
