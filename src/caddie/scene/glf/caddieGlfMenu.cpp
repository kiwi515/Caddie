#include "caddieGlfMenu.h"

#include <Sports2/Scene/Glf/Sp2GlfDefine.h>

using namespace Sp2;

namespace caddie
{
    GlfMenu::GlfMenu() :
        mRootPage("Golf Menu", sMenuPosX, sMenuPosY),
        mHole("Hole", 1, Glf::HOLE_MAX),
        mRepeatHole("Repeat Hole", true)
        // mPinType("Pin Type", 0, 0),
        // mWindDir("Wind Direction", 0, 0),
        // mWindSpd("Wind Speed", 0, 0),
        // mWindSpdRange("Wind Spd Range", 0, 0),
        // mApplyRestart("Apply and Restart", Action_ApplyRestart),
        // mQuitGame("Quit Game", Action_QuitGame),
    {
        mRootPage.AppendOption(&mHole);
        mRootPage.AppendOption(&mRepeatHole);
    }

    GlfMenu::~GlfMenu()
    {
    }

    const f32 GlfMenu::sMenuPosX = 100.0f;
    const f32 GlfMenu::sMenuPosY = 200.0f;
}