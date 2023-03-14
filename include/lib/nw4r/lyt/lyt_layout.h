#ifndef NW4R_LYT_LAYOUT_H
#define NW4R_LYT_LAYOUT_H
#include <revolution/MEM.h>
#include <types_nw4r.h>

namespace nw4r {
namespace lyt {

class Layout {
public:
    template <typename T> static void DeleteObj(T* t) {
        t->~T();
        FreeMemory(t);
    }

    static void FreeMemory(void* mem) { MEMFreeToAllocator(mspAllocator, mem); }

private:
    static MEMAllocator* mspAllocator;
};

} // namespace lyt
} // namespace nw4r

#endif
