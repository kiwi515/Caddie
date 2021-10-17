#include "caddieMemMgr.h"

#define CADDIE_MEM_SIZE (64 * 1024) // 64k

namespace caddie
{
    using namespace EGG;

    void MemManager::Initialize()
    {
        // NULL heap uses sAllocatableHeap
        sHeap = ExpHeap::create(CADDIE_MEM_SIZE, NULL, 0);
        CADDIE_ASSERT_EX(sHeap != NULL, "Main game heap creation failed!!!\n");
        CADDIE_LOG_EX("Game heap: @0x%08X -> 0x%08X\n", &sHeap, sHeap);
    }

    EGG::ExpHeap *MemManager::sHeap;
}