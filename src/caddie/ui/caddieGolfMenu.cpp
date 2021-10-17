#include "caddieGolfMenu.h"
#include "caddieMenuIntOption.h"
#include "caddieMenuEnumOption.h"
#include "caddieMenuActionOption.h"
#include "caddieAssert.h"

#include <RPSysSceneCreator.h>

#include <Sp2Scene.h>
#include <Sp2GlfDefine.h>
#include <Sp2StaticMem.h>

#include "ut_Color.h"

namespace caddie
{
    using namespace nw4r;
    using namespace Sp2;

    void GolfMenu::Calc()
    {
        MenuBase::Calc();

        // Update pin setting
        MenuIntOption *holeOpt = (MenuIntOption *)GetOption("Hole");
        int hole = holeOpt->GetValue();

        MenuEnumOption *pinOpt = (MenuEnumOption *)GetOption("Pin Type");
        // Hole 18 has one pin
        pinOpt->SetEnabled((hole == 18) ? false : true);
        // Hole 1 has three pins
        pinOpt->SetMax((hole == 1) ? 3 : 6);
        // Holes 1/18 are not categorized as A/B
        pinOpt->SetTable((hole == 1 || (hole > 18 && hole < 22)) ? sSpecialPinTypes : sPinTypes);
    }

    bool GolfMenu::Action_ApplySettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);

        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);

        // Hole (zero-indexed)
        MenuIntOption *holeOption = (MenuIntOption *)menu->GetOption("Hole");
        sMem->setStaticVar(Glf::GLF_VAR_NEXTHOLE, holeOption->GetValue() - 1, false);

        // Pin type
        MenuEnumOption *pinOpt = (MenuEnumOption *)menu->GetOption("Pin Type");

        // Wind (Speed + direction)
        MenuIntOption *windSpeedOpt = (MenuIntOption *)menu->GetOption("Wind Speed (m/s)");
        MenuEnumOption *windDirOpt = (MenuEnumOption *)menu->GetOption("Wind Direction");
        sMem->setStaticVar(Glf::GLF_VAR_PACKEDWIND + (holeOption->GetValue() - 1), Glf::PackWind(windDirOpt->GetValue(), windSpeedOpt->GetValue()), false);

        // Reload scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        ut::Color fade(0, 0, 0, 255);
        creator->changeSceneAfterFade(-1, &fade);

        // Toggle menu
        return true;
    }

    bool GolfMenu::Action_QuitGame()
    {
        // Fade out to main menu scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        ut::Color fade(0, 0, 0, 255);
        creator->changeSceneAfterFade(Sp2::SP2_MAINMENU, &fade);
    }

    void GolfMenu::Build()
    {
        CADDIE_ASSERT(GetNumOptions() == 0);

        PushBack(new MenuIntOption("Hole", 1, Sp2::Glf::HOLE_MAX));
        PushBack(new MenuEnumOption("Pin Type", 0, 6, sPinTypes));
        PushBack(new MenuEnumOption("Wind Direction", 0, Sp2::Glf::SOUTHWEST, sWindDirections));
        PushBack(new MenuIntOption("Wind Speed (m/s)", 0, Sp2::Glf::WIND_MAX));
        PushBack(new MenuActionOption("Apply Settings", &Action_ApplySettings));
        PushBack(new MenuActionOption("Quit Game", &Action_QuitGame));
    }

    const char *GolfMenu::sWindDirections[] =
    {
        "South",
        "Southeast",
        "East",
        "Northeast",
        "North",
        "Northwest",
        "West",
        "Southwest"
    };

    const char *GolfMenu::sPinTypes[] =
    {
        "Random",
        "Pin 1 (A)",
        "Pin 2 (A)",
        "Pin 3 (A)",
        "Pin 4 (B)",
        "Pin 5 (B)",
        "Pin 6 (B)"
    };

    // Used for holes that do not have pin sets by score (Hole 1, Hole 18)
    const char *GolfMenu::sSpecialPinTypes[] =
    {
        "Random",
        "Pin 1",
        "Pin 2",
        "Pin 3",
        "Pin 4",
        "Pin 5",
        "Pin 6"
    };
}