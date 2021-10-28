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

// Patch stubbed OSReport
// TO-DO: Make this work in C++
// Region free
kmBranchDefAsm(0x80061470, NULL)
{
    loc_0x0:
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stw r31, 0x7C(r1)
    bne- cr1, loc_0x34
    stfd f1, 0x28(r1)
    stfd f2, 0x30(r1)
    stfd f3, 0x38(r1)
    stfd f4, 0x40(r1)
    stfd f5, 0x48(r1)
    stfd f6, 0x50(r1)
    stfd f7, 0x58(r1)
    stfd f8, 0x60(r1)

    loc_0x34:
    addi r11, r1, 0x88
    addi r0, r1, 0x8
    lis r12, 0x100
    stw r3, 0x8(r1)
    addi r31, r1, 0x68
    stw r4, 0xC(r1)
    mr r4, r31
    stw r5, 0x10(r1)
    stw r6, 0x14(r1)
    stw r7, 0x18(r1)
    stw r8, 0x1C(r1)
    stw r9, 0x20(r1)
    stw r10, 0x24(r1)
    stw r12, 0x68(r1)
    stw r11, 0x6C(r1)
    stw r0, 0x70(r1)
    bl vprintf
    lwz r0, 0x84(r1)
    lwz r31, 0x7C(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr     
}

void loadMainCode()
{
    CADDIE_ASSERT_EX(OS_MAKER_CODE == '01', "Invalid disc game ID!\n");
    switch(OS_GAME_CODE)
    {
        case 'RZTE':
            loadKamekBinaryFromDisc(&cFunctionsNTSC_U.base, "/modules/main_NTSC_U.bin");
            break;
        case 'RZTP':
            CADDIE_BREAKPOINT;
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