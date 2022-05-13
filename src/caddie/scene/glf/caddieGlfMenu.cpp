#include "caddieGlfMenu.h"

#include <nw4r/ut/ut_Color.h>

#include <RPSystem/RPSysSceneCreator.h>

#include <Sports2/Scene/Glf/Sp2GlfDefine.h>

using namespace nw4r;
using namespace Sp2;

namespace caddie
{
    GlfMenu::GlfMenu() :
        mIsAwaitingSave(false),
        mRootPage("Golf Menu", sMenuPosX, sMenuPosY),
        mHole("Hole", 1, Glf::HOLE_MAX),
        mRepeatHole("Repeat Hole", true),
        // mPinType("Pin Type", 0, 0),
        // mWindDir("Wind Direction", 0, 0),
        // mWindSpd("Wind Speed", 0, 0),
        // mWindSpdRange("Wind Spd Range", 0, 0),
        // mApplyRestart("Apply and Restart", Action_ApplyRestart),
        mQuitGame("Quit Game", Action_QuitGame, this)
    {
        mRootPage.AppendOption(&mHole);
        mRootPage.AppendOption(&mRepeatHole);

        mRootPage.AppendOption(&mQuitGame);
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
        thisx->mRootPage.SaveChanges();
        thisx->mIsAwaitingSave = true;

        RPSysSceneCreator *creator = RPSysSceneCreator::getInstance();
        CADDIE_ASSERT(creator != NULL);
        creator->changeSceneAfterFade(-1,
            ut::Color(0, 0, 0, 255));
    }

    /**
     * @brief Quit game by returning to the menu scene
     */
    void GlfMenu::Action_QuitGame(void* menu)
    {
        CADDIE_ASSERT(menu != NULL);
        GlfMenu* thisx = (GlfMenu*)menu;
        thisx->mRootPage.DeleteChanges();
        thisx->mIsAwaitingSave = false;

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