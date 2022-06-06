#include <OS/OSError.h>
#include <OS/OSFatal.h>
#include <STL/stdarg.h>
#include <STL/stdio.h>
#include <SYSCONF/scapi.h>
#include <egg/util/eggException.h>
#include <loader/kamekLoader.h>
#include <loader/rzte.h>

void* allocAdapter(u32 size, bool isForCode, const loaderFunctions* funcs) {
    const loaderFunctionsEx* funcsEx = (const loaderFunctionsEx*)funcs;

    // Non-code is allocated in MEM2
    void* pHeap = (isForCode) ? *funcsEx->rootHeapMEM1 : *funcsEx->rootHeapMEM2;
    return funcsEx->eggAlloc(size, 32, pHeap);
}

void freeAdapter(void* memBlock, bool isForCode, const loaderFunctions* funcs) {
    const loaderFunctionsEx* funcsEx = (const loaderFunctionsEx*)funcs;

    // Non-code is allocated in MEM2
    void* pHeap = (isForCode) ? *funcsEx->rootHeapMEM1 : *funcsEx->rootHeapMEM2;
    funcsEx->eggFree(memBlock, pHeap);
}

void OSReport(const char* msg, ...) {
    va_list list;
    va_start(msg, list);
    vprintf(msg, list);
    va_end(list);
}
kmBranch(0x80061470, OSReport);

void loadMainCode() {
    switch (OS_GAME_CODE) {
    case 'RZTE':
        loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base,
                                "/modules/main_NTSC_U.bin");
        break;
    case 'RZTP':
        loadKamekBinaryFromDisc(&cFunctionsPAL.base, "/modules/main_PAL.bin");
        break;
    case 'RZTJ':
        loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base,
                                "/modules/main_NTSC_J.bin");
        break;
    case 'RZTK':
        loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base,
                                "/modules/main_KOR.bin");
        break;
    }
}
kmCall(CADDIE_ENTRYPOINT, loadMainCode);
