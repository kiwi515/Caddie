#ifndef LOADER_RZTE_H
#define LOADER_RZTE_H

#include "kamekLoader.h"
#include "types.h"
#include <STL/stdarg.h>

const u32 CADDIE_ENTRYPOINT = 0x80230f64;

typedef void * (* eggAlloc_t) (u32 size, s32 align, void *heap);
typedef void (* eggFree_t) (void *buffer, void *heap);
typedef void (* vprintf_t) (const char *, va_list);

void * allocAdapter(u32 size, bool isForCode, const loaderFunctions *funcs);
void freeAdapter(void *buffer, bool isForCode, const loaderFunctions *funcs);

struct loaderFunctionsEx
{
    loaderFunctions base;

    eggAlloc_t eggAlloc;
    eggFree_t eggFree;
    vprintf_t vaprintf;
    void **rootHeapMEM1;
    void **rootHeapMEM2;
};

const loaderFunctionsEx functions_us =
{
    {(OSReport_t)0x80235cc8,
    (OSFatal_t)0x800493a0,
    (DVDConvertPathToEntrynum_t)0x8009a620,
    (DVDFastOpen_t)0x8009a930,
    (DVDReadPrio_t)0x8009af50,
    (DVDClose_t)0x8009ac60,
    (sprintf_t)0x8000d168,
    allocAdapter,
    freeAdapter},
    
    (eggAlloc_t)0x801c1654,
    (eggFree_t)0x801c19c4,
    (vprintf_t)0x8000ceec,
    (void **)0x807ceb78, // &RPSysSystem::sRootMem1
    (void **)0x807ceb7c, // &RPSysSystem::sRootMem2
};

#endif