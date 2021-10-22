#include "caddieGolfMenu.h"
#include "caddieMenuIntOption.h"
#include "caddieMenuEnumOption.h"
#include "caddieMenuActionOption.h"
#include "caddieMenuBoolOption.h"
#include "caddieAssert.h"

#include <Sports2/Sp2Scene.h>
#include <Sports2/Sp2StaticMem.h>
#include <Glf/Sp2GlfMain.h>
#include <Glf/Sp2GlfDefine.h>

#include <RPSystem/RPSysSceneCreator.h>

#include <ut/ut_Color.h>

namespace caddie
{
    using namespace nw4r;
    using namespace Sp2;

    void GolfMenu::Build()
    {
        CADDIE_ASSERT(GetNumOptions() == 0);

        PushBackOption(new MenuIntOption("Hole", 1, Sp2::Glf::HOLE_MAX));
        
        MenuBoolOption *repeatOpt = new MenuBoolOption("Repeat Hole");
        repeatOpt->SetAllValue(true);
        PushBackOption(repeatOpt);

        PushBackOption(new MenuEnumOption("Pin Type", 0, 6, sPinTypes));
        PushBackOption(new MenuEnumOption("Wind Direction", 0, Sp2::Glf::SOUTHWEST, sWindDirections));
        PushBackOption(new MenuIntOption("Wind Speed (m/s)", 0, Sp2::Glf::WIND_MAX));
        PushBackOption(new MenuActionOption("Apply and Restart", &Action_SaveReload));
        PushBackOption(new MenuActionOption("Quit Game", &Action_QuitGame));
    }

    void GolfMenu::Calc()
    {
        MenuBase::Calc();

        // Update pin setting
        MenuIntOption *holeOpt = (MenuIntOption *)GetOption("Hole");
        int hole = holeOpt->GetSavedValue();

        MenuEnumOption *pinOpt = (MenuEnumOption *)GetOption("Pin Type");
        // Hole 18 has one pin
        pinOpt->SetEnabled((hole == 18) ? false : true);
        // Hole 1 has three pins
        pinOpt->SetMax((hole == 1) ? 3 : 6);
        // Holes 1/18 are not categorized as A/B
        pinOpt->SetTable((hole == 1 || (hole > 18 && hole < 22)) ? sSpecialPinTypes : sPinTypes);
    }

    void GolfMenu::ApplyHoleSettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);

        MenuIntOption *holeOption = (MenuIntOption *)menu->GetOption("Hole");
        // Hole option is one indexed
        sMem->setStaticVar(Glf::VAR_NEXTHOLE, holeOption->GetSavedValue() - 1, false);
    }

    void GolfMenu::ApplyWindSettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);

        // Hole option is one indexed
        int hole = ((MenuIntOption *)menu->GetOption("Hole"))->GetSavedValue() - 1;
        
        MenuIntOption *windSpeedOpt = (MenuIntOption *)menu->GetOption("Wind Speed (m/s)");
        MenuEnumOption *windDirOpt = (MenuEnumOption *)menu->GetOption("Wind Direction");
        u8 packedWind = Glf::PackWind(windDirOpt->GetSavedValue(), windSpeedOpt->GetSavedValue());

        sMem->setStaticVar(Glf::VAR_PACKEDWIND + hole, packedWind, false);
    }

    void GolfMenu::ApplyPinSettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        Glf::GlfMain *main = Glf::GlfMain::getInstance();
        CADDIE_ASSERT(main != NULL);

        MenuEnumOption *pinOpt = (MenuEnumOption *)menu->GetOption("Pin Type");
        if (!pinOpt->IsEnabled()) return;

        // Subtract 1 because of the "Random" index
        int pin = pinOpt->GetSavedValue() - 1;
        // Random not selected
        if (pin != -1) main->setPin(pin);
    }
    kmBranch(0x8040680c, &GolfMenu::ApplyPinSettings);

    MenuOptionBase::MenuCommand GolfMenu::Action_SaveReload()
    {
        // Commit changes to options
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        menu->SaveChanges();

        // Apply settings that are not overwritten by the scene
        // (Pin settings are applied later)
        ApplyHoleSettings();
        ApplyWindSettings();

        // Reload scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        ut::Color fade(0, 0, 0, 255);
        creator->changeSceneAfterFade(-1, &fade);

        return MenuOptionBase::MENU_HIDE;
    }

    MenuOptionBase::MenuCommand GolfMenu::Action_QuitGame()
    {
        // Revert unsaved changes
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        menu->DeleteChanges();

        // Fade out to main menu scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        ut::Color fade(0, 0, 0, 255);
        creator->changeSceneAfterFade(Sp2::SP2_MAINMENU, &fade);

        return MenuOptionBase::MENU_HIDE;
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

    // Used for holes that do not have pin sets by score (Hole 1, Hole 18, Holes 19-21)
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