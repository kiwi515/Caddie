#ifndef EGG_CORE_DVD_RIPPER_H
#define EGG_CORE_DVD_RIPPER_H
#include "types_egg.h"

namespace EGG {

class DvdRipper {
public:
    enum EAllocDirection { ALLOC_DIR_NONE, ALLOC_DIR_TOP, ALLOC_DIR_BOTTOM };

    static void* loadToMainRAM(const char*, u8*, Heap*, EAllocDirection, u32,
                               u32*, u32*);

private:
    static bool sErrorRetry;
};

} // namespace EGG

#endif
