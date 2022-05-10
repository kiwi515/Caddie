/********************************************************************************

         Kamek loader (custom code "entrypoint") integrated with Resort           

********************************************************************************/
#include <loader/kamekLoader.h>
#include <loader/rzte.h>
#include <core/caddieAssert.h>
#include <kernel/caddieDebug.h>
#include <OS/OSError.h>
#include <OS/OSFatal.h>
#include <SYSCONF/scapi.h>
#include <STL/stdarg.h>
#include <STL/stdio.h>

void * allocAdapter(u32 size, bool isForCode, const loaderFunctions *funcs)
{
    const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;

    // Non-code is allocated in MEM2
    void *pHeap = (isForCode) ? *funcsEx->rootHeapMEM1 : *funcsEx->rootHeapMEM2;
    return funcsEx->eggAlloc(size, 32, pHeap);
}

void freeAdapter(void *memBlock, bool isForCode, const loaderFunctions *funcs)
{
    const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
    
    // Non-code is allocated in MEM2
    void *pHeap = (isForCode) ? *funcsEx->rootHeapMEM1 : *funcsEx->rootHeapMEM2;
    funcsEx->eggFree(memBlock, pHeap);
}

void OSReport(const char *msg, ...)
{
    va_list list;
    va_start(msg, list);
    vprintf(msg, list);
    va_end(list);
}
kmBranch(0x80061470, OSReport);

void loadMainCode()
{
    CADDIE_ASSERT_EX(OS_MAKER_CODE == '01', "Invalid disc game ID!\n");
    switch(OS_GAME_CODE)
    {
        case 'RZTE':
            loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base, "/modules/main_NTSC_U.bin");
            break;
        case 'RZTP':
            loadKamekBinaryFromDisc(&cFunctionsPAL.base, "/modules/main_PAL.bin");
            break;
        case 'RZTJ':
            CADDIE_ASSERT_EX(false, "JP version is not supported yet!\n");
            loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base, "/modules/main_NTSC_J.bin");
            break;
        case 'RZTK':
            CADDIE_ASSERT_EX(false, "KR version is not supported yet!\n");
            loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base, "/modules/main_KOR.bin");
            break;
        default:
            CADDIE_ASSERT_EX(false, "Invalid game ID/game region!\n");
    }
} kmBranch(CADDIE_ENTRYPOINT, loadMainCode);