#include "caddiePreGameMgr.h"
#include "caddieAssert.h"
#include "eggController.h"
#include <Glf/Sp2GlfGameConfig.h>

namespace caddie
{
    using namespace Glf;
    using namespace EGG;

    void PreGameManager::setBlindFlag()
    {
        // Because the 1 and 2 Buttons are reserved for hole select,
        // blind golf is enabled by holding them both together

        u16 input = CoreControllerMgr::getInstance()->getNthController(0)->getButtons();
        if ((input & BTN_1) && (input & BTN_2))
        {
            GameConfig::getInstance()->setGlobalVar(VAR_BLINDFLAG, true, false);
        }

    } kmBranch(0x802287e4, &PreGameManager::setBlindFlag);

    u32 PreGameManager::getGameStartHole(CourseSelBtn lytBtn)
    {
        u32 base = getGameStartHoleFromBtn(lytBtn);

        u16 input = CoreControllerMgr::getInstance()->getNthController(0)->getButtons();
        // Holding 1 will add 1 to the starting hole; holding 2 will add 2.
        if (input & BTN_1)
        {
            return base + 1;
        }
        else if (input & BTN_2)
        {
            return base + 2;
        }

    } kmCall(0x80406968, &PreGameManager::getGameStartHole);

    u32 PreGameManager::getGameStartHoleFromBtn(CourseSelBtn lytBtn)
    {
        switch(lytBtn)
        {
            // Resort 3H
            case BTN_RESORT_A: return 0;
            case BTN_RESORT_B: return 3;
            case BTN_RESORT_C: return 6;
            // Classic 3H
            case BTN_CLASSIC_A: return 9;
            case BTN_CLASSIC_B: return 12;
            case BTN_CLASSIC_C: return 15;
            // Special 3H
            case BTN_SPECIAL: return 18;
            // 9H
            case BTN_RESORT_NINE: return 0;
            case BTN_CLASSIC_NINE: return 9;
            // 18H
            case BTN_EIGHTEEN_HOLE: return 0;

            default: return 0;
        }
    }
}