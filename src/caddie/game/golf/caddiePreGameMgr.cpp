#include "caddiePreGameMgr.h"
#include "caddieAssert.h"
#include "eggController.h"
#include <Glf/Sp2GlfGameConfig.h>
#include <Glf/Sp2GlfMain.h>

namespace caddie
{
    using namespace Glf;
    using namespace EGG;

    bool PreGameManager::canPlayNextHole()
    {
        GlfMain *pMain = GlfMain::getInstance();
        CADDIE_ASSERT(pMain != NULL);
        u32 hole = pMain->getCurrentHole();
        u32 gm = pMain->getGamemode();
        switch(gm)
        {
            case GM_RESORT_A:
            case GM_RESORT_B:
            case GM_RESORT_C:
            case GM_CLASSIC_A:
            case GM_CLASSIC_B:
            case GM_CLASSIC_C:
            case GM_SPECIAL:
                return true;
            
            case GM_RESORT_NINE:
                if (hole < 8) return true;

            case GM_CLASSIC_NINE:
            case GM_EIGHTEEN_HOLE:
                if (hole < 17) return true;

            default:
                return false;
        }
    }
    kmBranch(0x80406554, &PreGameManager::canPlayNextHole);

    void PreGameManager::setNextHole()
    {
        // GlfMain::sInstance is not set at this point so we need to use the instance in r29
        // Backup regs + GameConfig instance (r3)
        asm volatile
        (
            stwu r1, -0x80(r1)
            stmw r3, 0x8(r1)
        );

        register GlfMain *pMain;
    
        // GlfMain instance (r29 -> r3)
        asm
        (
            mr pMain, r29
        );

        CADDIE_ASSERT(pMain != NULL);
        u32 currentHole = pMain->getCurrentHole();
        u32 gm = pMain->getGamemode();

        // Restore regs + GameConfig instance
        asm volatile
        (
            lmw r3, 0x8(r1)
            addi r1, r1, 0x80
        );

        // 3 hole games will always repeat the current hole
        if (gm != GM_RESORT_NINE && gm != GM_CLASSIC_NINE && gm != GM_EIGHTEEN_HOLE)
        {
            GameConfig::getInstance()->setGlobalVar(VAR_NEXTHOLE, currentHole, false);
        }
        else
        {
            GameConfig::getInstance()->setGlobalVar(VAR_NEXTHOLE, currentHole + 1, false);
        }

    } 
    kmCall(0x80406998, &PreGameManager::setNextHole);
    kmCall(0x804069f0, &PreGameManager::setNextHole);

    void PreGameManager::setBlindFlag()
    {
        // Because the 1 and 2 Buttons are reserved for hole select,
        // blind golf is enabled by holding them both together

        u16 input = CoreControllerMgr::getInstance()->getNthController(0)->getButtons();
        if ((input & BTN_1) && (input & BTN_2))
        {
            GameConfig::getInstance()->setGlobalVar(VAR_BLINDFLAG, true, false);
        }
    }
    kmCall(0x802287e4, &PreGameManager::setBlindFlag);

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

        return base;
    }
    kmCall(0x80406968, &PreGameManager::getGameStartHole);

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