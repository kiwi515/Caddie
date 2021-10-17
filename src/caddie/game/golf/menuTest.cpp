#include "caddieAssert.h"
#include "caddieGolfMenu.h"

namespace caddie
{
    void testMenu()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Calc();
        #ifndef NDEBUG
        menu->DumpAll(500.0f, 200.0f);
        #endif
        menu->Draw(100.0f, 200.0f);
    }
    kmBranch(0x804116a0, &testMenu);
}