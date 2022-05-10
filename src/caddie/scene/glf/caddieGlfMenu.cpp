#include "caddieGlfMenu.h"

#include <Sports2/Glf/Sp2GlfDefine.h>

using namespace Sp2;

namespace caddie
{
    GlfMenu::GlfMenu() :
        mHole("Hole", 1, Glf::HOLE_MAX),
        mRepeatHole("Repeat Hole", 0, 1, true),
        // mPinType("Pin Type", 0, 0),
        // mWindDir("Wind Direction", 0, 0),
        // mWindSpd("Wind Speed", 0, 0),
        // mWindSpdRange("Wind Spd Range", 0, 0),
        // mApplyRestart("Apply and Restart", Action_ApplyRestart),
        // mQuitGame("Quit Game", Action_QuitGame),
    {
    }

    GlfMenu::~GlfMenu()
    {
    }
}