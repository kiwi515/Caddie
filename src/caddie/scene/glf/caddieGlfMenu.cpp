#include "caddieGlfMenu.h"
#include "caddieGlfMessage.h"

#include <nw4r/ut/ut_Color.h>

#include <RPSystem/RPSysSceneCreator.h>

#include <Sports2/Scene/Glf/Sp2GlfDefine.h>

using namespace nw4r;

namespace caddie
{
    GlfMenu::GlfMenu() :
        MenuBase(MSG_MENU_TITLE, sMenuPosX, sMenuPosY),
        mHole(MSG_HOLE, 1, Sp2::Glf::HOLE_MAX),
        mRepeatHole(MSG_REPEAT_HOLE, true),
        mPinType(MSG_PIN_TYPE, ENUM_PIN_TYPE, 0, CADDIE_ENUM_MAX(ENUM_PIN_TYPE)),
        mWindDir(MSG_WIND_DIR, ENUM_WIND_DIR, 0, CADDIE_ENUM_MAX(ENUM_WIND_DIR)),
        mWindSpd(MSG_WIND_SPD, ENUM_WIND_SPD, 0, WIND_SPD_RANDOM),
        mWindSpdRange(MSG_WIND_SPD_RANGE, ENUM_WIND_SPD_RANGE, 0, CADDIE_ENUM_MAX(ENUM_WIND_SPD_RANGE)),
        mApplyRestart(MSG_APPLY, Action_ApplyRestart, this),
        mQuitGame(MSG_QUIT, Action_QuitGame, this)
    {
        // Build root page
        GetRootPage().AppendOption(&mHole);
        GetRootPage().AppendOption(&mRepeatHole);
        GetRootPage().AppendOption(&mPinType);
        GetRootPage().AppendOption(&mWindDir);
        GetRootPage().AppendOption(&mWindSpd);
        GetRootPage().AppendOption(&mWindSpdRange);
        GetRootPage().AppendOption(&mApplyRestart);
        GetRootPage().AppendOption(&mQuitGame);
    }

    GlfMenu::~GlfMenu()
    {
    }

    /**
     * @brief Save menu settings and reload scene
     */
    void GlfMenu::Action_ApplyRestart(void* menu)
    {
        CADDIE_ASSERT(menu != NULL);
        GlfMenu* thisx = (GlfMenu*)menu;
        // Save all options' changes
        thisx->SaveChanges();
        // Ask scene to apply settings
        thisx->SetAwaitingApply(true);
        // Do not delete menu on scene re-init
        thisx->SetCanDelete(false);

        // Reload golf scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        creator->changeSceneAfterFade(-1, ut::Color(0, 0, 0, 255));
    }

    /**
     * @brief Quit game by returning to the menu scene
     */
    void GlfMenu::Action_QuitGame(void* menu)
    {
        CADDIE_ASSERT(menu != NULL);
        GlfMenu* thisx = (GlfMenu*)menu;
        // Delete all options' changes
        thisx->DeleteChanges();
        // Ask scene not to apply settings
        thisx->SetAwaitingApply(false);
        // Delete menu when returning
        thisx->SetCanDelete(true);

        // Return to title scene
        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        creator->changeSceneAfterFade(RPSysSceneCreator::SCENE_TITLE,
            ut::Color(0, 0, 0, 255));
    }

    //! @brief Menu X screen position
    const f32 GlfMenu::sMenuPosX = 100.0f;
    //! @brief Menu Y screen position
    const f32 GlfMenu::sMenuPosY = 200.0f;
}