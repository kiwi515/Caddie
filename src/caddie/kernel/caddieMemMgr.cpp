#include "caddieMemMgr.h"

#define CADDIE_MEM_SIZE (64 * 1024) // 64k

namespace caddie {

void MemManager::Initialize() {
    // Child of sAllocatableHeap
    sHeap = EGG::ExpHeap::create(CADDIE_MEM_SIZE, NULL, 0);
    CADDIE_ASSERT_EX(sHeap != NULL, "Main game heap creation failed!!!");
    CADDIE_LOG_EX("Game heap: @0x%08X -> 0x%08X\n", &sHeap, sHeap);
}

EGG::ExpHeap* MemManager::sHeap;
} // namespace caddie
