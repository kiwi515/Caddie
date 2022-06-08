#include "caddieGlfSceneHook.h"

#include "caddieAssert.h"
#include "caddieGlfMenu.h"
#include "caddieGlfUtil.h"
#include "caddieMenuMgr.h"

#include <Sports2/Sp2StaticMem.h>
#include <Sports2/Sp2Util.h>
#include <Sports2/scene/Glf/Sp2GlfDefine.h>
#include <Sports2/scene/Glf/Sp2GlfMain.h>

namespace caddie {

/**
 * @brief Golf scene configure (enter) callback
 *
 * @param scene Current scene
 */
void GlfSceneHook::OnConfigure(RPSysScene* scene) {
    // Setup menu
    if (sGlfMenu == NULL) {
        sGlfMenu = new GlfMenu();
        CADDIE_ASSERT(sGlfMenu != NULL);
    }

    // Open menu root
    MenuMgr::GetInstance().OpenMenu(sGlfMenu);
}

/**
 * @brief Golf scene calculate callback
 *
 * @param scene Current scene
 */
void GlfSceneHook::OnCalculate(RPSysScene* scene) {}

/**
 * @brief Golf scene user draw callback
 *
 * @param scene Current scene
 */
void GlfSceneHook::OnUserDraw(RPSysScene* scene) {}

/**
 * @brief Golf scene exit callback
 *
 * @param scene Current scene
 */
void GlfSceneHook::OnExit(RPSysScene* scene) {
    // Do not delete menu if settings are waiting to be applied
    if (GetMenu().CanDelete()) {
        delete sGlfMenu;
        sGlfMenu = NULL;
    }
    // Apply static mem settings
    else {
        Apply_StaticMem();
    }
}

/**
 * @brief Apply hole settings from menu
 */
void GlfSceneHook::Apply_Hole() {
    // Update hole
    Sp2::StaticMem::getInstance().setStaticVar(
        Sp2::Glf::VAR_NEXTHOLE, GetMenu().GetHoleInternal(), false);
}

/**
 * @brief Allow hole to be repeated if option is set
 */
void GlfSceneHook::Apply_RepeatHole() {
    Sp2::StaticMem& mem = Sp2::StaticMem::getInstance();

    if (GetMenu().GetRepeatHole()) {
        const int nextHole = mem.getStaticVar(Sp2::Glf::VAR_NEXTHOLE, false);
        mem.setStaticVar(Sp2::Glf::VAR_NEXTHOLE, nextHole - 1, false);
    }
}

/**
 * @brief Apply pin settings from menu
 */
void GlfSceneHook::Apply_Pin() {
    Sp2::Glf::GlfMain& main = Sp2::Glf::GlfMain::getInstance();

    // Next pin type
    int pin = GetMenu().GetPinType();

    // Next hole to be played determines how to interpret pin value
    int nextHole = 0;
    if (GetMenu().GetRepeatHole()) {
        // Value is internal hole num (zero indexed)
        nextHole = main.getCurrentHole() + 1;
    } else {
        nextHole = GetMenu().GetHole();
    }

    // Adjust pin value
    switch (nextHole) {
    // Hole 1
    case 1:
        switch (pin) {
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
        switch (pin) {
        // Random pin 1-6
        case SP_PIN_RND_ALL:
            pin = Sp2::Rand(6);
            break;
        }
        break;

    // Holes 2-17
    default:
        switch (pin) {
        // Do not update pin
        case PIN_SCORE:
            pin = main.getPin();
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
    main.setPin(pin);
}

/**
 * @brief Apply wind settings from menu
 */
void GlfSceneHook::Apply_Wind() {
    int spd = GetMenu().GetWindSpd();
    int dir = GetMenu().GetWindDir();

    // Random wind speed
    if (spd == WIND_SPD_RANDOM) {
        // Wind range
        int min = 0;
        int max = Sp2::Glf::WIND_MAX;

        switch (GetMenu().GetWindSpdRange()) {
        // 0-10 m/s (0-20 mph)
        case RANGE_0_10:
            max = 10;
            break;
        // 0-5 m/s (0-10 mph)
        case RANGE_0_5:
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

    Sp2::StaticMem::getInstance().setStaticVar(
        Sp2::Glf::VAR_WIND + GetMenu().GetHoleInternal(),
        Sp2::Glf::PackWind(dir, spd), false);
}

/**
 * @brief Apply menu settings which require StaticMem
 */
void GlfSceneHook::Apply_StaticMem() {
    Apply_Wind();

    // Hole option should not automatically be applied
    if (GetMenu().IsAwaitingApply()) {
        Apply_Hole();
        GetMenu().SetAwaitingApply(false);
    }
}

/**
 * @brief Apply menu settings which require GlfMain
 */
void GlfSceneHook::Apply_GlfMain() {
    Apply_RepeatHole();
    Apply_Pin();
}
kmBranch(0x8040680c, GlfSceneHook::Apply_GlfMain);

/**
 * @brief Disable Golf tutorial
 */
bool GlfSceneHook::ShouldShowTutorial() { return false; }
kmBranch(0x803fa370, GlfSceneHook::ShouldShowTutorial);

/**
 * @brief Check whether the next hole can be played
 * @note Repeat Hole option prevents game from ending
 */
bool GlfSceneHook::CanPlayNextHole() {
    return GetMenu().GetRepeatHole() ? true : !GlfUtil::IsNextRoundOver();
}
kmBranch(0x80406554, GlfSceneHook::CanPlayNextHole);

/**
 * @brief Number of holes played in the match
 * @details Fixes infinite recursion bug
 */
u32 GlfSceneHook::GetNumHolesPlayed() {
    // First hole of gamemode
    const u32 gmFirst = GlfUtil::GetGamemodeNthHoleInternal(0);
    // Current hole
    const u32 gmCurrent = Sp2::Glf::GlfMain::getInstance().getCurrentHole();

    // Avoid returning negative result
    if (gmCurrent < gmFirst) {
        return 0;
    }

    // Vanilla behavior
    return gmCurrent - gmFirst;
}
kmBranch(0x80405f1c, GlfSceneHook::GetNumHolesPlayed);

/**
 * @brief Access golf menu
 */
GlfMenu& GlfSceneHook::GetMenu() {
    CADDIE_ASSERT(sGlfMenu != NULL);
    return *sGlfMenu;
}

GlfMenu* GlfSceneHook::sGlfMenu = NULL;

} // namespace caddie
