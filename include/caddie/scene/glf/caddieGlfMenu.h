#ifndef CADDIE_SCENE_GLF_GLFMENU_H
#define CADDIE_SCENE_GLF_GLFMENU_H
#include "types_caddie.h"
#include "caddieMenuPage.h"
#include "caddieMenuOption.h"

namespace caddie
{
    /**
     * @brief Golf scene menu
     */
    class GlfMenu
    {
    public:
        GlfMenu();
        virtual ~GlfMenu();

        MenuPage* GetRootPage() { return &mRootPage; }

        bool IsAwaitingSave() const { return mIsAwaitingSave; }
        void SetAwaitingSave(bool save) { mIsAwaitingSave = save; }

        static void Action_QuitGame(void* menu);

    private:
        //! @brief Prevents menu from being deleted on scene exit
        bool mIsAwaitingSave;
        //! @brief Menu root
        MenuPage mRootPage;

        MenuIntOption mHole;
        MenuBoolOption mRepeatHole;
        // MenuEnumOption mPinType;
        // MenuEnumOption mWindDir;
        // MenuEnumOption mWindSpd;
        // MenuEnumOption mWindSpdRange;
        // MenuActionOption mApplyRestart;
        MenuActionOption mQuitGame;

        static const f32 sMenuPosX;
        static const f32 sMenuPosY;
    };
}

#endif