#ifndef NW4R_UT_LOCKED_CACHE_H
#define NW4R_UT_LOCKED_CACHE_H
#include <OS.h>
#include <types_nw4r.h>

namespace nw4r {
namespace ut {
namespace LC {

void Enable();
void Disable();

bool Lock();
void Unlock();

void LoadBlocks(void* dst, void* src, u32 size);
void StoreBlocks(void* dst, void* src, u32 size);
void StoreData(void* dst, void* src, u32 size);

static void QueueWaitEx(u32 num) {
    while (LCQueueLength() != num) {
        OSYieldThread();
    }
}

} // namespace LC
} // namespace ut
} // namespace nw4r

#endif
