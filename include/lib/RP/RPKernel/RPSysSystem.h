#ifndef RP_KERNEL_SYSTEM_H
#define RP_KERNEL_SYSTEM_H
#include "types_caddie.h"

class RPSysSystem {
public:
    static EGG::Heap* getSystemHeap() { return sSystemHeap; }

private:
    static EGG::Heap* sSystemHeap;
};

#endif
