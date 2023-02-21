#ifndef EGG_CORE_HEAP_H
#define EGG_CORE_HEAP_H
#include "eggDisposer.h"
#include "types_egg.h"

#include <RevoSDK/MEM.h>
#include <nw4r/ut.h>

#define MB_AS_B (1024.0f * 1024.0f)
#define KB_AS_B (1024.0f)

namespace EGG {

struct Heap : Disposer {
    enum EHeapKind { HEAP_EXPANDED = 1, HEAP_FRAME = 2 };

    Heap(MEMiHeapHead*);
    virtual ~Heap();
    virtual EHeapKind getHeapKind() const = 0;
    virtual void initAllocator(Allocator*, s32) = 0;
    virtual void* alloc(u32, s32) = 0;
    virtual void free(void*) = 0;
    virtual void destroy() = 0;
    virtual u32 resizeForMBlock(void*, u32) = 0;
    virtual UNKTYPE VIRTUAL_0x24(UNKTYPE) = 0;
    virtual u32 getAllocatableSize(s32) = 0;
    virtual u32 adjust() = 0;

    static void initialize();
    static void* alloc(u32, int, Heap*);
    static Heap* findHeap(MEMiHeapHead*);
    Heap* findParentHeap();
    static Heap* findContainHeap(const void*);
    static void free(void*, Heap*);
    void dispose();
    Heap* becomeCurrentHeap();
};

} // namespace EGG

void* operator new(size_t);
void* operator new(size_t, EGG::Heap*, int);
void* operator new[](size_t);
void* operator new[](size_t, int);
void* operator new[](size_t, EGG::Heap*, int);
void operator delete(void*);
void operator delete[](void*);

#endif
