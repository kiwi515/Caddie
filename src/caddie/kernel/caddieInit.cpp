#include "caddieInit.h"
#include "caddieAssert.h"
#include "caddieDebug.h"
#include "caddieMemMgr.h"

namespace caddie
{
    void Main()
    {
        MemManager::Initialize();
        InitCpp();

        #ifndef NDEBUG
        SetExceptionCallback();
        #endif
    }
    kmBranch(0x8022dc14, &Main);

    void InitCpp()
    {
        CADDIE_ASSERT(__ctor_loc != NULL);
        CADDIE_LOG_EX("__ctor_loc=%08X\n", __ctor_loc);
        
        for (StaticCtor *p = &__ctor_loc; p < &__ctor_end; p++)
        {
            (*p)();
        }
    }
}