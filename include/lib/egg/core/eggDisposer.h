#ifndef EGG_CORE_DISPOSER_H
#define EGG_CORE_DISPOSER_H
#include "types_egg.h"

#include <nw4r/ut.h>

namespace EGG {

struct Disposer {
    Disposer();
    virtual ~Disposer();

    Heap* mHeap;
    nw4r::ut::Node mNode;
};

} // namespace EGG

#endif
