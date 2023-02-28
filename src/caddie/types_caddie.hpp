#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include <RP/types_rp.h>
#include <Sports2/types_sp2.h>
#include <egg/types_egg.h>
#include <nw4r/types_nw4r.h>
#include <types.h>

//

#include <kernel/caddieAssert.h>
#include <kernel/caddieRuntime.hpp>

/**
 * New
 */
void* operator new(size_t size);
void* operator new(size_t size, EGG::Heap* heap);
/**
 * New array
 */
void* operator new[](size_t size);
void* operator new[](size_t size, EGG::Heap* heap);
/**
 * Delete
 */
void operator delete(void* block);
void operator delete(void* block, EGG::Heap* heap);
/**
 * Delete array
 */
void operator delete[](void* block);
void operator delete[](void* block, EGG::Heap* heap);

#endif
