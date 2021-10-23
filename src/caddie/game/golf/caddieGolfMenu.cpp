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

#include "caddieGolfMenu.inc.cpp"

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

        PushBackOption(new MenuEnumOption("Pin Type", 0, ARRAY_COUNT(sPinTypes) - 1, sPinTypes));
        PushBackOption(new MenuEnumOption("Wind Direction", 0, ARRAY_COUNT(sWindDirections) - 1, sWindDirections));
        PushBackOption(new MenuEnumOption("Wind Speed (m/s)", 0, ARRAY_COUNT(sWindSpeeds) - 1, sWindSpeeds));
        PushBackOption(new MenuEnumOption("Random Wind Speed", 0, ARRAY_COUNT(sRandWindSpdRanges) - 1, sRandWindSpdRanges));
        PushBackOption(new MenuActionOption("Apply and Restart", &Action_SaveReload));
        PushBackOption(new MenuActionOption("Quit Game", &Action_QuitGame));
    }

    void GolfMenu::Calc()
    {
        MenuBase::Calc();

        // Update pin setting
        MenuIntOption *holeOpt = (MenuIntOption *)GetOption("Hole");
        int hole = holeOpt->GetUnsavedValue();

        MenuEnumOption *pinOpt = (MenuEnumOption *)GetOption("Pin Type");
        // Hole 18 has one pin
        pinOpt->SetEnabled((hole == 18) ? false : true);
        // Hole 1 has three pins
        pinOpt->SetMax((hole == 1) ? 4 : ARRAY_COUNT(sPinTypes) - 1);
        // Holes 1/18 are not categorized as A/B
        pinOpt->SetTable((hole == 1 || (hole > 18 && hole < 22)) ? sSpecialPinTypes : sPinTypes);

        // Toggle random spd range option
        MenuEnumOption *spdOpt = (MenuEnumOption *)GetOption("Wind Speed (m/s)");
        MenuEnumOption *spdRangeOpt = (MenuEnumOption *)GetOption("Random Wind Speed");
        spdRangeOpt->SetEnabled(spdOpt->GetUnsavedValue() == SPD_RANDOM);
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
        
        MenuEnumOption *windSpeedOpt = (MenuEnumOption *)menu->GetOption("Wind Speed (m/s)");
        int spd = windSpeedOpt->GetSavedValue();
        MenuEnumOption *windDirOpt = (MenuEnumOption *)menu->GetOption("Wind Direction");        
        int dir = windDirOpt->GetSavedValue();

        int minspd = 0;
        int maxspd = Glf::WIND_MAX;
        if (windSpeedOpt->GetSavedValue() == SPD_RANDOM)
        {
            MenuEnumOption *spdRangeOpt = (MenuEnumOption *)menu->GetOption("Random Wind Speed");
            switch(spdRangeOpt->GetSavedValue())
            {
                case RANGE_0_10:
                    minspd = 0; maxspd = 10;
                    break;
                case RANGE_0_5:
                    minspd = 0; maxspd = 5;
                    break;
                case RANGE_5_10:
                    minspd = 5; maxspd = 10;
                    break;
                case RANGE_10_15:
                    minspd = 10; maxspd = 15;
                    break;
                case RANGE_0_15:
                    minspd = 0; maxspd = 15;
                    break;
            }
        }

        spd = (spd == SPD_RANDOM) ? (Sp2::Rand(minspd, maxspd)) : spd;
        dir = (dir == DIR_RANDOM) ? (Sp2::Rand() % Glf::MAX_WIND_DIV) : dir;

        u8 packedWind = Glf::PackWind(dir, spd);

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

        int pin = pinOpt->GetSavedValue();
        switch(pin)
        {
            case PIN_FROMSCORE:
                break;
            case PIN_RANDOM:
                switch(main->getCurrentHole() + 1)
                {
                    // Hole 1 has 3 pins
                    case 1:
                        main->setPin(Sp2::Rand() % 3);
                        break;
                    // Hole 18 has 1 pin
                    case 18:
                        main->setPin(0);
                        break;
                    // All other holes have 6 pins
                    default:
                        main->setPin(Sp2::Rand() % 6);
                        break;
                }
                break;
            default:
                main->setPin(pin - PIN_MAX);
                break;
        }
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
}