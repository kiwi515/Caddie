#include "caddieAssert.h"
#include "caddieGlfSceneHook.h"
#include "caddieGlfMenu.h"
#include "caddieMenuMgr.h"

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
        MenuMgr::GetInstance().OpenPage(sGlfMenu->GetRootPage());
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
        delete sGlfMenu;
        sGlfMenu = NULL;
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