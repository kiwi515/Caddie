#include "caddieGolfMenu.h"
#include "caddieMenuIntOption.h"
#include "caddieMenuActionOption.h"
#include "caddieAssert.h"

#include <RPSysSceneCreator.h>

#include <Sp2GlfDefine.h>
#include <Sp2StaticMem.h>

#include "ut_Color.h"

namespace caddie
{
    using namespace nw4r;

    void GolfMenu::Calc()
    {
        MenuBase::Calc();
    }

    bool GolfMenu::Action_SaveAndExit()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        // Hole (zero-indexed)
        MenuIntOption *holeOption = (MenuIntOption *)menu->GetOption((int)GOLFMENU_HOLE);
        Sp2::StaticMem::getInstance()->setStaticVar(Sp2::Glf::GLF_VAR_NEXTHOLE, holeOption->GetValue() - 1, false);

        // White fade is used to easily distinguish from a restart
        ut::Color fade(255, 255, 255, 255);
        // -1 to Reload scene
        RPSysSceneCreator::getInstance()->changeSceneAfterFade(-1, &fade);

        // Toggle menu
        return true;
    }

    void GolfMenu::Build()
    {
        CADDIE_ASSERT(GetNumOptions() == 0);

        PushBack(new MenuIntOption("Hole", 1, Sp2::Glf::HOLE_MAX));
        PushBack(new MenuActionOption("Save And Exit", &Action_SaveAndExit));
    }
}