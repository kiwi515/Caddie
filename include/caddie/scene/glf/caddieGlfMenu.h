#ifndef CADDIE_SCENE_GLF_GLFMENU_H
#define CADDIE_SCENE_GLF_GLFMENU_H
#include "types_caddie.h"
#include "caddieMenuBase.h"
#include "caddieMenuPage.h"
#include "caddieMenuOption.h"


namespace caddie
{
    /**
     * @brief Golf scene menu
     */
    class GlfMenu : public MenuBase
    {
    public:
        GlfMenu();
        virtual ~GlfMenu();

        static void Action_ApplyRestart(void* menu);
        static void Action_QuitGame(void* menu);

    private:
        MenuIntOption mHole;
        MenuBoolOption mRepeatHole;
        MenuEnumOption mPinType;
        MenuEnumOption mWindDir;
        MenuEnumOption mWindSpd;
        MenuEnumOption mWindSpdRange;
        MenuActionOption mApplyRestart;
        MenuActionOption mQuitGame;

        static const f32 sMenuPosX;
        static const f32 sMenuPosY;
    };
}

#endif