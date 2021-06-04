#ifndef EGG_CORE_HEAP_H
#define EGG_CORE_HEAP_H
#include "types_egg.h"

namespace EGG
{
    class Heap
    {

    };
}

void * operator new(size_t);
void * operator new(size_t, EGG::Heap *, int);
void * operator new[](size_t);
void * operator new[](size_t, int);
void * operator new[](size_t, EGG::Heap *, int);
void operator delete(void *);
void operator delete[](void *);

#endif