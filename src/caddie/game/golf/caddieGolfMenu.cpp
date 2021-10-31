#include "caddieGolfMenu.h"
#include "caddieMenuIntOption.h"
#include "caddieMenuEnumOption.h"
#include "caddieMenuLocalizedEnumOption.h"
#include "caddieMenuActionOption.h"
#include "caddieMenuBoolOption.h"
#include "caddieAssert.h"
#include "caddieGolfUtil.h"

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
        PushBackOption(&(new MenuBoolOption("Repeat Hole"))->SetAllValue(true));
        PushBackOption(new MenuEnumOption("Pin Type", 0, ARRAY_COUNT(sPinTypeEnum) - 1, sPinTypeEnum));
        PushBackOption(new MenuEnumOption("Wind Direction", 0, ARRAY_COUNT(sWindDirectionEnum) - 1, sWindDirectionEnum));
        PushBackOption(new MenuLocalizedEnumOption(sWindSpeedNames, 0, ARRAY_COUNT(sWindSpeedEnum_Mph) - 1, sWindSpeedLocale));
        PushBackOption(new MenuLocalizedEnumOption(sWindSpdRangeNames, 0, ARRAY_COUNT(sWindSpdRangeEnum_Mph) - 1, sWindSpdRangeLocale));
        PushBackOption(new MenuActionOption("Apply and Restart", &Action_SaveReload));
        // PushBackOption(new MenuActionOption("Restart (Don't save)", &Action_ReloadNoSave));
        PushBackOption(new MenuActionOption("Quit Game", &Action_QuitGame));
    }

    void GolfMenu::Calc()
    {
        MenuBase::Calc();

        Localizer *local = Localizer::GetInstance();
        CADDIE_ASSERT(local != NULL);

        // Update pin setting
        int hole = GET_OPTION(MenuIntOption, "Hole")->GetUnsavedValue();

        MenuEnumOption *pinOpt = GET_OPTION(MenuEnumOption, "Pin Type");
        // Hole 18 has one pin
        pinOpt->SetEnabled((hole == 18) ? false : true);
        
        // Holes 1/18 are not categorized as A/B
        // This also removes the "Random A"/"Random B" options
        if (hole == 1)
        {
            pinOpt->SetTable(sPinTypeHoleOneEnum);
        }
        else if (hole >= 19 && hole <= 21)
        {
            pinOpt->SetTable(sPinTypeSpecialEnum);
        }
        else
        {
            pinOpt->SetTable(sPinTypeEnum);
        }

        if (pinOpt->IsNullSelect()) pinOpt->SetUnsavedValue(PIN_1);

        // Toggle random spd range option
        MenuEnumOption *spdOpt = GET_OPTION(MenuEnumOption, local->Localize(sWindSpeedNames));
        MenuEnumOption *spdRangeOpt = GET_OPTION(MenuEnumOption, local->Localize(sWindSpdRangeNames));
        spdRangeOpt->SetEnabled(spdOpt->GetUnsavedValue() == SPD_RANDOM);
    }

    void GolfMenu::Reset()
    {
        Localizer *local = Localizer::GetInstance();
        CADDIE_ASSERT(local != NULL);

        GET_OPTION(MenuIntOption, "Hole")->SetAllValue(1);
        GET_OPTION(MenuBoolOption, "Repeat Hole")->SetAllValue(true);
        GET_OPTION(MenuEnumOption, "Pin Type")->SetAllValue(0);
        GET_OPTION(MenuEnumOption, "Wind Direction")->SetAllValue(0);
        GET_OPTION(MenuLocalizedEnumOption, local->Localize(sWindSpeedNames))->SetAllValue(1);
        GET_OPTION(MenuLocalizedEnumOption, local->Localize(sWindSpdRangeNames))->SetAllValue(1);
    }

    // Prevent invalid settings from being applied across holes due to "Repeat Hole" being disabled
    void GolfMenu::Validate()
    {
        int hole = GET_OPTION(MenuIntOption, "Hole")->GetSavedValue();
        // Prepare for next hole if we are not repeating
        if (!GET_OPTION(MenuBoolOption, "Repeat Hole")->GetSavedValue()) hole++;

        MenuEnumOption *pinOpt = GET_OPTION(MenuEnumOption, "Pin Type"); 
        int pin = pinOpt->GetSavedValue();
        switch(hole)
        {
            // Hole 1 has three pins
            case 0:
                if (pin >= PIN_4 && pin <= PIN_6) pinOpt->SetAllValue(PIN_1);
                else if (pin == PIN_RANDOM_A || pin == PIN_RANDOM_B) pinOpt->SetAllValue(PIN_RANDOM_ALL);
                break;

            // Hole 18 has one pin
            case 17:
                if (pin >= PIN_2 && pin < PIN_MAX) pinOpt->SetAllValue(PIN_1);
                break;

            // Special holes have six pins, but are not sorted by difficulty
            case 18:
            case 19:
            case 20:
                if (pin == PIN_RANDOM_A || pin == PIN_RANDOM_B) pinOpt->SetAllValue(PIN_RANDOM_ALL);
                break;
        }
    }

    void GolfMenu::ApplyHoleSettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);

        // Hole option is one indexed
        sMem->setStaticVar(Glf::VAR_NEXTHOLE, 
            GET_OPTION_STATIC(menu, MenuIntOption, "Hole")->GetSavedValue() - 1,
            false);
    }

    void GolfMenu::ApplyWindSettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        StaticMem *sMem = StaticMem::getInstance();
        CADDIE_ASSERT(sMem != NULL);
        Localizer *local = Localizer::GetInstance();
        CADDIE_ASSERT(local != NULL);

        // Hole option is one indexed
        int hole = GET_OPTION_STATIC(menu, MenuIntOption, "Hole")->GetSavedValue() - 1;

        int spd = GET_OPTION_STATIC(menu, MenuEnumOption, local->Localize(sWindSpeedNames))->GetSavedValue();
        int dir = GET_OPTION_STATIC(menu, MenuEnumOption, "Wind Direction")->GetSavedValue();
        
        // Decide on random wind range (only when speed setting is set to "Random")
        int minspd = 0;
        int maxspd = Glf::WIND_MAX;
        if (spd == SPD_RANDOM)
        {
            MenuEnumOption *spdRangeOpt = GET_OPTION_STATIC(menu, MenuEnumOption, local->Localize(sWindSpdRangeNames));
            switch(spdRangeOpt->GetSavedValue())
            {
                // 0-20 mph (18 hole)
                case RANGE_0_10:
                    minspd = 0; maxspd = 10;
                    break;
                // 0-10 mph (A)
                case RANGE_0_5:
                    minspd = 0; maxspd = 5;
                    break;
                // 10-20 mph (B)
                case RANGE_5_10:
                    minspd = 5; maxspd = 10;
                    break;
                // 20-30 mph (C)
                case RANGE_10_15:
                    minspd = 10; maxspd = 15;
                    break;
                // 0-30 (Special)
                case RANGE_0_15:
                    minspd = 0; maxspd = 15;
                    break;
            }

            spd = Sp2::Rand(minspd, maxspd);
        }

        dir = (dir == DIR_RANDOM) ? (Sp2::Rand(Glf::MAX_WIND_DIV)) : dir;

        // Set packed wind data
        u8 packedWind = Glf::PackWind(dir, spd);
        sMem->setStaticVar(Glf::VAR_PACKEDWIND + hole, packedWind, false);
    }

    void GolfMenu::ApplyPinSettings()
    {
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        Glf::GlfMain *main = Glf::GlfMain::getInstance();
        CADDIE_ASSERT(main != NULL);

        MenuEnumOption *pinOpt = GET_OPTION_STATIC(menu, MenuEnumOption, "Pin Type");
        if (!pinOpt->IsEnabled()) return;

        int pin = pinOpt->GetSavedValue();
        switch(pin)
        {
            case PIN_FROMSCORE:
                break;
            case PIN_RANDOM_ALL:
                u32 max = GetHoleMaxPin(main->getCurrentHole());
                main->setPin(Sp2::Rand(max));
                break;
            case PIN_RANDOM_A:
                main->setPin(Sp2::Rand(3, 6));
                break;
            case PIN_RANDOM_B:
                main->setPin(Sp2::Rand(0, 3));
                break;
            default:
                main->setPin(pin);
                break;
        }
    }
#ifdef CADDIE_REGION_NTSC_U
    kmBranch(0x8040680c, &GolfMenu::ApplyPinSettings);
#elif CADDIE_REGION_PAL
    kmBranch(0x80406b2c, &GolfMenu::ApplyPinSettings);
#endif

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

    MenuOptionBase::MenuCommand GolfMenu::Action_ReloadNoSave()
    {
        // Simply reload the scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        ut::Color fade(0, 0, 0, 255);
        creator->changeSceneAfterFade(-1, &fade);

        return MenuOptionBase::MENU_HIDE;
    }

    MenuOptionBase::MenuCommand GolfMenu::Action_QuitGame()
    {
        // Reset settings
        GolfMenu *menu = GolfMenu::GetInstance();
        CADDIE_ASSERT(menu != NULL);
        menu->Reset();

        // Fade out to main menu scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        ut::Color fade(0, 0, 0, 255);
        creator->changeSceneAfterFade(Sp2::SP2_MAINMENU, &fade);

        return MenuOptionBase::MENU_HIDE;
    }
}