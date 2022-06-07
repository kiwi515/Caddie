#ifndef EGG_CORE_DVD_RIPPER_H
#define EGG_CORE_DVD_RIPPER_H
#include "types_egg.h"

namespace EGG {

class DvdRipper {
public:
    enum EAllocDirection { ALLOC_DIRECTION_0, ALLOC_DIRECTION_1 };

    static void* loadToMainRAM(const char*, u8*, Heap*, EAllocDirection, u32,
                               u32*, u32*);

private:
    static bool sErrorRetry;
};

} // namespace EGG

#endif
