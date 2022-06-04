#ifndef LOADER_RZTE_H
#define LOADER_RZTE_H

#include "kamekLoader.h"
#include "types.h"
#include <STL/stdarg.h>

#ifdef CADDIE_REGION_NTSC_U
    const u32 CADDIE_ENTRYPOINT = 0x80230f64;
#elif CADDIE_REGION_PAL
    const u32 CADDIE_ENTRYPOINT = 0x80231230;
#else
    const u32 CADDIE_ENTRYPOINT = 0x00000000;
#endif

extern u32 OS_GAME_CODE : 0x80000000;
extern u16 OS_MAKER_CODE : 0x80000004;

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

const loaderFunctionsEx cFunctionsNTSC_U =
{
    {(OSReport_t)0x80061470,
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

const loaderFunctionsEx cFunctionsPAL =
{
    {(OSReport_t)0x80061470,
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
    (void **)0x807cf278, // &RPSysSystem::sRootMem1
    (void **)0x807cf27c, // &RPSysSystem::sRootMem2
};

#endif
