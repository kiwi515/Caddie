#include "caddieGolfMisc.h"
#include "caddieGolfMenu.h"
#include "caddieMenuIntOption.h"
#include "caddieMenuBoolOption.h"

#include <Sp2GlfMain.h>
#include <Sp2GlfDefine.h>
#include <Sp2StaticMem.h>
#include <Sp2Scene.h>

#include <RPSysSysWinMgr.h>
#include <RPSysSceneMgr.h>

namespace caddie
{
    using namespace Sp2;

    bool CanPlayNextHole(const Glf::GlfMain *pMain)
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        MenuBoolOption *repeatOpt = (MenuBoolOption *)menu->GetOption("Repeat Hole");
        CADDIE_ASSERT(repeatOpt != NULL);

        CADDIE_BREAKPOINT;
        if (repeatOpt->GetValue()) return true;

        int hole = pMain->getCurrentHole();
        switch(pMain->getGamemode())
        {
            case Glf::GM_RESORT_A:
                return (hole < 2);
            case Glf::GM_RESORT_B:
                return (hole < 5);
            case Glf::GM_RESORT_C:
                return (hole < 8);
            case Glf::GM_RESORT_NINE:
                return (hole < 8);

            case Glf::GM_CLASSIC_A:
                return (hole < 11);
            case Glf::GM_CLASSIC_B:
                return (hole < 14);
            case Glf::GM_CLASSIC_C:
                return (hole < 17);
            case Glf::GM_CLASSIC_NINE:
            case Glf::GM_EIGHTEEN_HOLE:
                return (hole < 17);

            case Glf::GM_SPECIAL:
                return (hole < 20);
        }
    }
    kmBranch(0x80406554, &CanPlayNextHole);

    void RepeatHoleIL()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        MenuBoolOption *repeatOpt = (MenuBoolOption *)menu->GetOption("Repeat Hole");
        if (!repeatOpt->GetValue()) return;

        MenuIntOption *holeOpt = (MenuIntOption *)menu->GetOption("Hole");
        CADDIE_ASSERT(holeOpt != NULL);

        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);

        sMem->setStaticVar(Glf::GLF_VAR_NEXTHOLE, holeOpt->GetValue() - 1, false);
    }
    kmBranch(0x80406a5c, &RepeatHoleIL);

    void DisablePause()
    {
        RPSysSysWinMgr *winMgr = RPSysSysWinMgr::getInstance();
        CADDIE_ASSERT(winMgr != NULL);

        RPSysSceneMgr *sceneMgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(sceneMgr != NULL);

        // Disable pausing in the golf scene
        if (sceneMgr->getCurrentSceneID() != SP2_GOLF)
        {
            // Normal behavior
            if (winMgr->GetWord0x14() == -1)
            {
                // Not sure what this object is yet,
                // for now the call is in asm
                CADDIE_ASM_BEGIN
                    lis r3, 0x806f4cd0@h
                    lwz r3, 0x806f4cd0@l(r3)

                    lis r4, 0x802352d4@h
                    ori r4, r4, 0x802352d4@l
                    mtlr r4
                    blrl
                CADDIE_ASM_END
            }
        }

        // Peel back layer of stack because we return from DisablePause before the caller can return
        CADDIE_ASM_BEGIN
            opword 0x80010014
            opword 0x83e1000c
            opword 0x7c0803a6
            opword 0x38210010
        CADDIE_ASM_END
    }
    kmBranch(0x80232970, &DisablePause);
}