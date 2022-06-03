#ifndef EGG_CORE_EXPHEAP_H
#define EGG_CORE_EXPHEAP_H
#include "types_egg.h"
#include "eggHeap.h"
#include "eggDisposer.h"

namespace EGG
{
    struct ExpHeap : Heap
    {
        virtual ~ExpHeap();
        virtual EHeapKind getHeapKind() const;
        virtual void initAllocator(Allocator *, s32);
        virtual void * alloc(u32, s32);
        virtual void free(void *);
        virtual void destroy();
        virtual u32 resizeForMBlock(void *, u32);
        virtual UNKTYPE VIRTUAL_0x24(UNKTYPE);
        virtual u32 getAllocatableSize(s32);
        virtual u32 adjust();

        static ExpHeap * create(void *, u32, u16);
        static ExpHeap * create(u32, Heap *, u16);
    };
}

#endif