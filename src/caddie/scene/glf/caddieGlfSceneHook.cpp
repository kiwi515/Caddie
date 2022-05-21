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

        Sp2::StaticMem* mem = Sp2::StaticMem::getInstance();
        CADDIE_ASSERT(mem != NULL);

        // Update hole
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
        int nextHole;
        if (sGlfMenu->GetRepeatHole()) {
            nextHole = main->getCurrentHole();
        }
        else {
            nextHole = sGlfMenu->GetHole();
        }

        // Adjust pin value
        switch(nextHole)
        {
            // Hole 1
            case 0:
                switch(pin)
                {
                    // Random pin 1-3
                    case H1_PIN_RND_ALL:
                        pin = Sp2::Rand(3);
                        break;
                }
                break;

            // Hole 18
            case 17:
                pin = PIN_1;
                break;

            // Special Course (19-21)
            case 18:
            case 19:
            case 20:
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