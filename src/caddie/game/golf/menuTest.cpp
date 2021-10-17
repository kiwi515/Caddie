#include "caddieAssert.h"
#include "caddieGolfMenu.h"

namespace caddie
{
    void testMenu()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        menu->Calc();
        menu->Draw(100.0f, 200.0f);
    }
    kmBranch(0x804116a0, &testMenu);
}