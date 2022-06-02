#include "caddieAssert.h"
#include "caddieGlfSceneHook.h"
#include "caddieGlfMenu.h"
#include "caddieMenuMgr.h"

#include <Sports2/Sp2StaticMem.h>
#include <Sports2/Sp2Util.h>
#include <Sports2/scene/Glf/Sp2GlfMain.h>
#include <Sports2/scene/Glf/Sp2GlfDefine.h>

namespace caddie
{
    /**
     * @brief Golf scene configure (enter) callback
     * 
     * @param scene Current scene 
     */
    void GlfSceneHook::OnConfigure(RPSysScene* scene)
    {
        // Setup menu
        if (sGlfMenu == NULL) {
            sGlfMenu = new GlfMenu();
            CADDIE_ASSERT(sGlfMenu != NULL);
        }

        // Hide menu
        MenuMgr::GetInstance().SetVisible(false);
        // Open menu root
        MenuMgr::GetInstance().OpenPage(&sGlfMenu->GetRootPage());
    }

    /**
     * @brief Golf scene calculate callback
     * 
     * @param scene Current scene 
     */
    void GlfSceneHook::OnCalculate(RPSysScene* scene)
    {
        MenuMgr::GetInstance().Calc();
    }

    /**
     * @brief Golf scene user draw callback
     * 
     * @param scene Current scene 
     */
    void GlfSceneHook::OnUserDraw(RPSysScene* scene)
    {
        MenuMgr::GetInstance().Draw();
    }

    /**
     * @brief Golf scene exit callback
     * 
     * @param scene Current scene 
     */
    void GlfSceneHook::OnExit(RPSysScene* scene)
    {
        CADDIE_ASSERT(sGlfMenu != NULL);

        // Do not delete menu if settings are waiting to be applied
        if (!sGlfMenu->IsAwaitingSave()) {
            delete sGlfMenu;
            sGlfMenu = NULL;
        }
    }

    /**
     * @brief Apply hole settings from menu
     */
    void GlfSceneHook::Apply_Hole()
    {
        // Repeat current hole
        if (sGlfMenu->GetRepeatHole()) {
            return;
        }

        // Update hole
        Sp2::StaticMem* mem = Sp2::StaticMem::getInstance();
        CADDIE_ASSERT(mem != NULL);
        mem->setStaticVar(Sp2::Glf::VAR_NEXTHOLE, sGlfMenu->GetHole(), false);
    }

    /**
     * @brief Apply pin settings from menu
     */
    void GlfSceneHook::Apply_Pin()
    {
        Sp2::Glf::GlfMain* main = Sp2::Glf::GlfMain::getInstance();
        CADDIE_ASSERT(main != NULL);

        Sp2::StaticMem* mem = Sp2::StaticMem::getInstance();
        CADDIE_ASSERT(mem != NULL);

        // Next pin type
        int pin = sGlfMenu->GetPinType();

        // Next hole to be played determines how to interpret pin value
        int nextHole = 0;
        if (sGlfMenu->GetRepeatHole()) {
            // Value is internal hole num (zero indexed)
            nextHole = main->getCurrentHole() + 1;
        }
        else {
            nextHole = sGlfMenu->GetHole();
        }

        // Adjust pin value
        switch(nextHole)
        {
            // Hole 1
            case 1:
                switch(pin)
                {
                    // Random pin 1-3
                    case H1_PIN_RND_ALL:
                        pin = Sp2::Rand(3);
                        break;
                }
                break;

            // Hole 18
            case 18:
                pin = PIN_1;
                break;

            // Special Course (19-21)
            case 19:
            case 20:
            case 21:
                switch(pin)
                {
                    // Random pin 1-6
                    case SP_PIN_RND_ALL:
                        pin = Sp2::Rand(6);
                        break;
                }
                break;

            // Holes 2-17
            default:
                switch(pin)
                {
                    // Do not update pin
                    case PIN_SCORE:
                        pin = main->getPin();
                        break;
                    // Random pin 1-6
                    case PIN_RND_ALL:
                        pin = Sp2::Rand(6);
                        break;
                    // Random pin 4-6
                    case PIN_RND_A:
                        pin = Sp2::Rand(3, 6);
                        break;
                    // Random pin 1-3
                    case PIN_RND_B:
                        pin = Sp2::Rand(3);
                        break;
                }
                break;
        }

        // Apply pin
        main->setPin(pin);
    }

    /**
     * @brief Apply wind settings from menu
     */
    void GlfSceneHook::Apply_Wind()
    {
        Sp2::StaticMem* mem = Sp2::StaticMem::getInstance();
        CADDIE_ASSERT(mem != NULL);

        int spd = sGlfMenu->GetWindSpd();
        int dir = sGlfMenu->GetWindDir();

        // Random wind speed
        if (spd == WIND_SPD_RANDOM) {
            // Wind range
            int min = 0;
            int max = Sp2::Glf::WIND_MAX;

            switch(sGlfMenu->GetWindSpdRange())
            {
                // 0-10 m/s (0-20 mph)
                case RANGE_0_10:
                    min = 0;
                    max = 10;
                    break;
                // 0-5 m/s (0-10 mph)
                case RANGE_0_5:
                    min = 0;
                    max = 5;
                    break;
                // 5-10 m/s (10-20 mph)
                case RANGE_5_10:
                    min = 5;
                    max = 10;
                    break;
                // 10-15 m/s (20-30 mph)
                case RANGE_10_15:
                    min = 10;
                    max = 15;
                    break;
                // 0-15 m/s (0-30 mph)
                case RANGE_0_15:
                    // Min/max initialized to 0-15
                    break;
            }

            // Generate random speed
            spd = Sp2::Rand(min, max);
        }

        // Random direction
        if (dir == DIR_RND) {
            dir = Sp2::Rand(Sp2::Glf::MAX_WIND_DIV);
        }

        mem->setStaticVar(Sp2::Glf::VAR_WIND + sGlfMenu->GetHoleInternal(),
            Sp2::Glf::PackWind(dir, spd), false);
    }

    /**
     * @brief Access golf menu
     */
    GlfMenu* GlfSceneHook::GetMenu()
    {
        return sGlfMenu;
    }

    GlfMenu* GlfSceneHook::sGlfMenu = NULL;
}