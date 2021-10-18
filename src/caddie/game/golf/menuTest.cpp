#include "caddieAssert.h"
#include "caddieGolfMenu.h"

namespace caddie
{
    bool testMenu(bool b)
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Calc();
        // menu->DumpAll(500.0f, 200.0f);
        menu->Draw(100.0f, 200.0f);

        return b;
    }
    kmBranch(0x804116a0, &testMenu);
}