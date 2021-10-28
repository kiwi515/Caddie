#include "caddieGolfMisc.h"
#include "caddieGolfMenu.h"
#include "caddieMenuIntOption.h"
#include "caddieMenuBoolOption.h"
#include "caddieMenuEnumOption.h"

#include <Sp2Obj806f4cd0.h>
#include <Sp2GlfMain.h>
#include <Sp2GlfDefine.h>
#include <Sp2StaticMem.h>
#include <Sp2Scene.h>

#include <RPSysSysMsgWinMgr.h>
#include <RPSysSceneMgr.h>
#include <RPSysSceneCreator.h>

#include <ut/ut_Color.h>

namespace caddie
{
    using namespace nw4r;
    using namespace Sp2;

    bool CanPlayNextHole(const Glf::GlfMain *pMain)
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        if (GET_OPTION_STATIC(menu, MenuBoolOption, "Repeat Hole")->GetSavedValue()) return true;

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
            case Glf::GM_CLASSIC_NINE:
            case Glf::GM_EIGHTEEN_HOLE:
                return (hole < 17);

            case Glf::GM_SPECIAL:
                return (hole < 20);
        }
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x80406554, &CanPlayNextHole);
#elif CADDIE_REGION_PAL
    kmBranch(0x80406874, &CanPlayNextHole);
#endif

    void RepeatHoleIL()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);

        if (!GET_OPTION_STATIC(menu, MenuBoolOption, "Repeat Hole")->GetSavedValue()) return;

        // Hole option is one indexed
        int hole = GET_OPTION_STATIC(menu, MenuIntOption, "Hole")->GetSavedValue() - 1;
        sMem->setStaticVar(Glf::VAR_NEXTHOLE, hole, false);
    }

    void DisablePause()
    {
        RPSysSysMsgWinMgr *winMgr = RPSysSysMsgWinMgr::getInstance();
        CADDIE_ASSERT(winMgr != NULL);

        RPSysSceneMgr *sceneMgr = RPSysSceneMgr::getInstance();
        CADDIE_ASSERT(sceneMgr != NULL);

        // Disable pausing in the golf scene
        if (sceneMgr->getCurrentSceneID() != SP2_GOLF)
        {
            // Normal behavior
            if (winMgr->GetWord0x14() == -1)
            {
                Obj806f4cd0::GetInstance()->func_802352d4();
            }
        }

        // Peel back layer of stack because we return from DisablePause before the caller can return
        // (Region free)
        CADDIE_ASM_BEGIN
            opword 0x80010014
            opword 0x83e1000c
            opword 0x7c0803a6
            opword 0x38210010
        CADDIE_ASM_END
    }
    
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x80232970, &DisablePause);
#elif CADDIE_REGION_PAL
    kmBranch(0x80232c3c, &DisablePause);
#endif

    // Disable AB check sequence
    bool HasDoneABCheck()
    {
        return true;
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x8026a298, &HasDoneABCheck);
#elif CADDIE_REGION_PAL
    kmBranch(0x8026a5b8, &HasDoneABCheck);
#endif

}