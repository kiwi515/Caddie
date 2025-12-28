#include "caddieGlfSceneHook.h"

#include "caddieGlfMenu.h"
#include "caddieGlfPostMenu.h"
#include "caddieGlfUtil.h"
#include "caddieInputMgr.h"
#include "caddieMenuMgr.h"

#include <RPGraphics/RPGrpRenderer.h>
#include <RevoSDK/MTX.h>
#include <Sports2/Scene/Glf/RPGlfBall.h>
#include <Sports2/Scene/Glf/RPGlfClub.h>
#include <Sports2/Scene/Glf/RPGlfClubManager.h>
#include <Sports2/Scene/Glf/RPGlfFieldManager.h>
#include <Sports2/Scene/Glf/RPGlfPlayerManager.h>
#include <Sports2/Scene/Glf/RPGlfSimManager.h>
#include <Sports2/Scene/Glf/RPGlfUtility.h>
#include <Sports2/Scene/Glf/Sp2GlfConfig.h>
#include <Sports2/Scene/Glf/Sp2GlfDefine.h>
#include <Sports2/Scene/Glf/Sp2GlfMain.h>
#include <Sports2/Scene/Glf/Sp2GlfSequenceMgr.h>
#include <Sports2/Sp2StaticMem.h>
#include <Sports2/Sp2Util.h>
#include <egg/gfx.h>
#include <nw4r/ut.h>

// Calculate absolute value.
#define ABS(x) ((x) > 0.0f ? (x) : (-x))

// Take the maximum of two values.
#define MAX(x, y) ((x) > (y) ? (x) : (y))
// Take the minimum of two values.
#define MIN(x, y) ((x) < (y) ? (x) : (y))

// Clamp a value to the specified range.
#undef CLAMP
#define CLAMP(low, high, x)                                                    \
    ((x) < (low) ? (low) : ((x) > (high) ? (high) : (x)))

// Convert meters to world units.
#define M(X) ((f32)(X) * 10.0f)
// Convert yards to world units.
#define YD(X) ((f32)(X) * 10.0f / 1.094f)

kmWrite32(0x803f8778, 0x60000000);
kmWrite32(0x803f878c, 0x60000000);

namespace caddie {

bool GlfSceneHook::sDidStopShot = false;

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
    if (sGlfPostMenu == NULL) {
        sGlfPostMenu = new GlfPostMenu();
        CADDIE_ASSERT(sGlfPostMenu != NULL);
    }

    // Open menu root
    MenuMgr::GetInstance().OpenMenu(sGlfMenu);
}

/**
 * @brief Golf scene calculate callback
 *
 * @param scene Current scene
 */
void GlfSceneHook::OnCalculate(RPSysScene* scene) {
    bool isMenuOpen = MenuMgr::GetInstance().IsVisible();
    Sp2::Glf::GlfMain::getInstance().setPause(isMenuOpen);

    if (MenuMgr::GetInstance().GetMenu() == NULL) {
        MenuMgr::GetInstance().OpenMenu(sGlfMenu);
    }
}

void GlfSceneHook::OnPausedSeqMgrCalc() {
    if (MenuMgr::GetInstance().IsVisible()) {
        return;
    }

    Sp2::Glf::SequenceMgr::getInstance().Calculate();
}
kmCall(0x804175e8, GlfSceneHook::OnPausedSeqMgrCalc);

void GlfSceneHook::OnNextShot() {
    if (sDidStopShot || !GetMenu().GetRetryShotMenu()) {
        Sp2::Glf::SequenceMgr::getInstance().GetSequenceMain()->NextShot();
        GlfPostMenu::ChangePhase();

        sDidStopShot = false;
        return;
    }

    if (MenuMgr::GetInstance().IsVisible()) {
        MenuMgr::GetInstance().CloseMenu();
        MenuMgr::GetInstance().SetVisible(false);
    }

    MenuMgr::GetInstance().OpenMenu(sGlfPostMenu);
    MenuMgr::GetInstance().SetVisible(true);
}
kmCall(0x803f8754, GlfSceneHook::OnNextShot);

void GlfSceneHook::OnUserDraw(RPSysScene* scene) {
    if (!MenuMgr::GetInstance().IsVisible()) {
        return;
    }

    if (MenuMgr::GetInstance().GetMenu() != sGlfMenu) {
        return;
    }

    char buffer[1024];

    // Current pin display
    {
        u32 hole = Sp2::Glf::GlfConfig::getInstance().getCurrentHole();
        u32 pin = Sp2::Glf::GlfConfig::getInstance().getPin();

        if (hole == 0) {
            snprintf(buffer, sizeof(buffer), "Current Pin: %s",
                     ENUM_PIN_TYPE_HOLE1[pin]);
        } else if (hole > 17) {
            snprintf(buffer, sizeof(buffer), "Current Pin: %s",
                     ENUM_PIN_TYPE_SPECIAL[pin]);
        } else {
            snprintf(buffer, sizeof(buffer), "Current Pin: %s",
                     ENUM_PIN_TYPE[pin]);
        }

        Sp2::PrintOutline(buffer, 0xFF00FFFF, 0xFF000000, false, 100.0f,
                          180.0f);
    }

    ;
}

void GlfSceneHook::DrawPutterGuide(const nw4r::math::VEC3* pPoints, u16 num,
                                   GXColor color, u8 width) {

    static const f32 sc_MinDistPutter = M(5.0);
    static const f32 sc_MaxDistPutter = M(20.0);

    RPGlfPlayer& player = RPGlfPlayerManager::GetInstance().GetCurrentPlayer();

    const nw4r::math::VEC3& pin_pos =
        RPGlfFieldManager::getInstance().GetPinPos();

    nw4r::math::VEC2 vd(player.GetAvatarPos().x - pin_pos.x,
                        player.GetAvatarPos().z - pin_pos.z);

    f32 pin_to_avatar_dist = nw4r::math::FSqrt(vd.x * vd.x + vd.y * vd.y);

    // Vector from the pin to the player position
    nw4r::math::VEC2 pin_to_avatar;
    RPGlfUtility::CalcDeltaXZ(pin_to_avatar, player.GetAvatarPos(),
                              RPGlfFieldManager::getInstance().GetPinPos());

    f32 pin_avatar_angle_deg =
        RPGlfUtility::CalcDeltaAngle2D(pin_to_avatar, player.GetAvatarAngle());
    pin_avatar_angle_deg = ABS(pin_avatar_angle_deg);
    pin_avatar_angle_deg = NW4R_MATH_RAD_TO_DEG(pin_avatar_angle_deg);

    f32 dist_min = sc_MinDistPutter;
    f32 dist_max = sc_MaxDistPutter;
    CADDIE_ASSERT(dist_min < dist_max);

    // Putt distance clamped to the bounds
    f32 dist_clamp = CLAMP(dist_min, dist_max, pin_to_avatar_dist);

    // Range of the distance bounds
    f32 range = dist_max - dist_min;

    // Calculate angle threshold for a replay
    f32 threshold;
    if (range == 0.0f) {
        threshold = 6.5f;
    } else {
        threshold = (dist_clamp - dist_min) * -6.5f / range + 6.5f;
    }

    bool too_short = pin_to_avatar_dist < sc_MinDistPutter;
    bool is_replay = pin_avatar_angle_deg >= threshold;

    // Putter guide line
    {
        if (too_short) {
            color.r = 0;
            color.g = 0;
            color.b = 255;
        } else if (is_replay) {
            color.r = 0;
            color.g = 255;
            color.b = 0;
        } else {
            color.r = 255;
            color.g = 0;
            color.b = 0;
        }

        if (!GetMenu().GetReplayInfo()) {
            color.r = 32;
            color.g = 64;
            color.b = 255;
        }

        EGG::DrawGX::DrawLineStrip(pPoints, num, color, width);
    }
}
kmCall(0x803fab74, GlfSceneHook::DrawPutterGuide);

void GlfSceneHook::DrawReplaySphere() {
    if (RPGrpRenderer::GetDrawPass() != RPGrpRenderer::EDrawPass_DrawXLU) {
        return;
    }

    bool world_dl = RPGrpRenderer::GetViewID() == 1;
    bool map_dl = RPGrpRenderer::GetViewID() == 5 &&
                  !RPGlfFieldManager::getInstance().IsHideUI();

    if (!world_dl && !map_dl) {
        return;
    }

    if (!GetMenu().GetReplayInfo()) {
        return;
    }

    if (RPGlfClubManager::getInstance().GetActiveClub()->GetType() ==
        RPGlfClub::EType_PT) {
        return;
    }

    RPGlfPlayer& player = RPGlfPlayerManager::GetInstance().GetCurrentPlayer();

    const nw4r::math::VEC3& pin_pos =
        RPGlfFieldManager::getInstance().GetPinPos();

    nw4r::math::VEC2 vd(player.GetAvatarPos().x - pin_pos.x,
                        player.GetAvatarPos().z - pin_pos.z);

    f32 pin_to_avatar_dist = nw4r::math::FSqrt(vd.x * vd.x + vd.y * vd.y);

    bool bigger_range =
        player.GetBall()->IsHitFlag() || player.GetBall()->IsHitPole();

    f32 dist_min = YD(30);
    f32 dist_max = YD(200);
    CADDIE_ASSERT(dist_min < dist_max);

    f32 dist_clamp = CLAMP(dist_min, dist_max, pin_to_avatar_dist);

    f32 range = dist_max - dist_min;
    CADDIE_ASSERT(range > 0.0f);

    f32 c0 = bigger_range ? M(3.0) : M(0.5);
    f32 c1 = bigger_range ? M(10.0) : M(1.5);
    f32 c2 = bigger_range ? M(3.0) : M(0.5);
    f32 threshold = (c1 - c0) * (dist_clamp - dist_min) / range + c2;

    f32 ball_to_pin_dist = player.GetBall()->GetDistFromPin();
    bool in_range = ball_to_pin_dist <= threshold;

    nw4r::math::MTX34 old = EGG::DrawGX::s_cameraMtx;
    {
        nw4r::math::MTX34 mtx;
        PSMTXIdentity(mtx);
        PSMTXScaleApply(mtx, mtx, threshold, threshold, threshold);
        PSMTXTransApply(mtx, mtx, pin_pos.x, pin_pos.y, pin_pos.z);

        nw4r::ut::Color color;

        if (in_range) {
            color.r = 0;
            color.g = 255;
            color.b = 0;
        } else {
            if (bigger_range) {
                color.r = 0;
                color.g = 0;
                color.b = 255;
            } else {
                color.r = 255;
                color.g = 0;
                color.b = 0;
            }
        }

        if (RPGrpRenderer::GetViewID() == 1) {
            color.a = 100;
        } else if (RPGrpRenderer::GetViewID() == 5) {
            color.a = 255;
        } else {
            CADDIE_ASSERT(false);
        }

        EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_NORMAL);
        EGG::DrawGX::BeginDrawSphere();
        EGG::DrawGX::DrawDLWorld(EGG::DrawGX::DL_SPHERE_8X16, mtx, color);
    }
    EGG::DrawGX::s_cameraMtx = old;
}
kmBranch(0x80404b10, GlfSceneHook::DrawReplaySphere);

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
    Sp2::Glf::GlfConfig& main = Sp2::Glf::GlfConfig::getInstance();

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
        spd = Sp2::Rand(min, max + 1);
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
 * @brief Apply menu settings which require GlfConfig
 */
void GlfSceneHook::Apply_GlfConfig() {
    Apply_RepeatHole();
    Apply_Pin();
}
kmBranch(0x8040680c, GlfSceneHook::Apply_GlfConfig);

/**
 * @brief Allow shot to be canceled by holding B + MINUS + 2
 * @details Forces shot to end while removing the stroke penalty
 */
void GlfSceneHook::OnGlfBallCalc(RPGlfBall* ball, u32 frame, u32) {
    CADDIE_ASSERT(ball != NULL);

    static const u32 scStopShotBtns =
        InputMgr::BTN_B | InputMgr::BTN_MINUS | InputMgr::BTN_2;

    RPGlfBall* pSimBall = RPGlfSimManager::GetSimBall();
    CADDIE_ASSERT(pSimBall);

    if (pSimBall->GetLifetime() > 0) {
        const u32 held = InputMgr::GetInstance().Held(InputMgr::PLAYER_1);

        if ((held & scStopShotBtns) == scStopShotBtns) {
            // Remove OOB stroke penalty
            RPGlfPlayer& player =
                RPGlfPlayerManager::GetInstance().GetCurrentPlayer();
            player.SetStroke(player.GetStroke() - 2);

            // Mark ball as OOB, then force shot to end
            ball->SetCollision(RPGlfCollisionModel::COL_OB);
            ball->SetCollisionNoAir(RPGlfCollisionModel::COL_OB);
            ball->SetMoving(false);

            sDidStopShot = true;
        }
    }

    ball->Calc(frame);
}
kmCall(0x80414754, GlfSceneHook::OnGlfBallCalc);

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
    const u32 gmCurrent = Sp2::Glf::GlfConfig::getInstance().getCurrentHole();

    // Avoid returning negative result
    // TODO: Figure out why this is even needed. Maybe abs(curr - first) is more
    // robust?
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

GlfPostMenu& GlfSceneHook::GetPostMenu() {
    CADDIE_ASSERT(sGlfPostMenu != NULL);
    return *sGlfPostMenu;
}

GlfMenu* GlfSceneHook::sGlfMenu = NULL;
GlfPostMenu* GlfSceneHook::sGlfPostMenu = NULL;

} // namespace caddie
