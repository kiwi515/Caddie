#include "caddieMemMgr.h"

namespace caddie {

void MemManager::Initialize() {
    CADDIE_ASSERT_EX(sHeap == NULL, "MemManager already initialized!");

    // Child of sAllocatableHeap
    sHeap = EGG::ExpHeap::create(sHeapSize, NULL, 0);
    CADDIE_ASSERT_EX(sHeap != NULL, "Main game heap creation failed!!!");
}

EGG::ExpHeap* MemManager::sHeap = NULL;
u32 MemManager::sHeapSize = 64 * 1024; // 64KB

} // namespace caddie
