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

    private:
        MenuPage mRootPage;
        MenuPrimOption<int> mHole;
        MenuPrimOption<bool> mRepeatHole;
        MenuEnumOption mPinType;
        MenuEnumOption mWindDir;
        MenuEnumOption mWindSpd;
        MenuEnumOption mWindSpdRange;
        MenuActionOption mApplyRestart;
        MenuActionOption mQuitGame;
    };
}

#endif