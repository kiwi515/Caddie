#include "caddieSoundTestScene.hpp"

#include "caddieInputMgr.hpp"
#include "caddieSceneCreatorEx.hpp"

#include <RP/RPAudio.h>
#include <Sp2DrawMgr.h>
#include <Sp2Snd.h>
#include <Sp2Util.h>

namespace caddie {
namespace SoundTest {

#define X(y) #y,
const char* Scene::scSoundNames[] = {SP2_SND_SOUNDS};
#undef X

u32 Scene::GetNumSound() { return ARRAY_LENGTH(scSoundNames); }

u32 Scene::GetMaxSoundID() { return GetNumSound() - 1; }

Scene::Scene()
    : mSelectedSnd(0),
      mDisplayTopSnd(0),
      mBtnRepeatTimer(scRepeatTimerDefault),
      mHeldLastFrame(0),
      mSoundGroup(Group_Cmn) {}

void Scene::Calculate() {
    const u32 trig = InputMgr::GetInstance().Trig(InputMgr::PLAYER_1);
    const u32 held = InputMgr::GetInstance().Held(InputMgr::PLAYER_1);

    // Continue auto-repeat scrolling if the same D-Pad button is being held
    const bool stillHeld = (mHeldLastFrame & held) == mHeldLastFrame;
    if (!stillHeld) {
        ResetBtnRepeat();
    }

    // Move cursor down (PRESS)
    if (trig & InputMgr::BTN_DOWN) {
        CursorDown(1);
    }
    // Move cursor up (PRESS)
    else if (trig & InputMgr::BTN_UP) {
        CursorUp(1);
    }
    // Jump cursor down (PRESS)
    else if (trig & InputMgr::BTN_RIGHT) {
        CursorDown(scNumDisplay);
        DisplayDown(scNumDisplay);
    }
    // Jump cursor up (PRESS)
    else if (trig & InputMgr::BTN_LEFT) {
        CursorUp(scNumDisplay);
        DisplayUp(scNumDisplay);
    }
    // Move cursor down (HELD)
    else if (held & InputMgr::BTN_DOWN) {
        if (--mBtnRepeatTimer < 0) {
            CursorDown(1);
        }
    }
    // Move cursor up (HELD)
    else if (held & InputMgr::BTN_UP) {
        if (--mBtnRepeatTimer < 0) {
            CursorUp(1);
        }
    }

    // Scroll display down
    if (mSelectedSnd > GetDisplayBottomSnd()) {
        const int overFlow = mSelectedSnd - GetDisplayBottomSnd();
        DisplayDown(overFlow);
    }
    // Scroll display up
    else if (mSelectedSnd < mDisplayTopSnd) {
        const int underFlow = mDisplayTopSnd - mSelectedSnd;
        DisplayUp(underFlow);
    }

    // Play sound
    if (trig & InputMgr::BTN_A) {
        CADDIE_ASSERT(mSelectedSnd < GetNumSound());
        RPSndAudioMgr::stopAllSound();
        LoadGroupForSound(mSelectedSnd);
        RPSndAudioMgr::startSound(mSelectedSnd);
    }
    // Exit
    else if (trig & InputMgr::BTN_B) {
        SceneCreatorEx::GetInstance().changeSceneAfterFade(
            SceneCreatorEx::SCENE_DEBUG_ROOT, Color::BLACK);
    }

    mHeldLastFrame = held;
}

void Scene::UserDraw() {
    if (Sp2::DrawMgr::getDrawPass() == Sp2::DrawMgr::DrawPass_4) {
        DrawList();
        DrawScroll();
        DrawControls();
    }
}

void Scene::DrawList() {
    // Display list based on scroll position
    for (int i = 0; i < scNumDisplay; i++) {
        // Determine if this element is the highlighted sound
        const int absIndex = mDisplayTopSnd + i;
        CADDIE_ASSERT(absIndex < GetNumSound());
        const Color color =
            mSelectedSnd == absIndex ? scSelectedSoundColor : scSoundColor;

        // List element position
        const f32 x = scDisplayX;
        const f32 y = scDisplayY + (i * scDisplayLineFeed);

        // Draw list element
        Sp2::Printf(x, y, scDisplayScale, color.ToARGB(), false,
                    scSoundNames[absIndex]);
    }
}

void Scene::DrawScroll() {
    // Percentage of list scrolled
    const f32 scrollPcnt = static_cast<f32>(mDisplayTopSnd + scNumDisplay) /
                           static_cast<f32>(GetNumSound());
    // Convert percentage to position on bar
    const f32 markerY =
        scDisplayY + (scrollPcnt * (scScrollBarLineFeed * scNumScrollBar));

    // Display scroll bar
    for (int i = 0; i < scNumScrollBar; i++) {
        // Bar piece position
        const f32 x = scScrollBarX;
        const f32 y = scDisplayY + (i * scScrollBarLineFeed);
        // Draw bar piece
        Sp2::Printf(scScrollBarX, y, scScrollBarScale, scSoundColor.ToARGB(),
                    true, "|");
    }

    // Display scroll marker
    Sp2::PrintfOutline(scScrollBarX, markerY, scScrollMarkerScale,
                       scScrollMarkerColor.ToARGB(), Color::WHITE.ToARGB(),
                       true, "[X]");
}

void Scene::DrawControls() {
    Sp2::PrintOutline("Caddie Sound Test", Color::WHITE.ToARGB(),
                      Color::BLACK.ToARGB(), false, 50.0f, 100.0f, 2.0f);
    Sp2::PrintOutline("Move with D-Pad (U/D/L/R)", Color::WHITE.ToARGB(),
                      Color::BLACK.ToARGB(), false, 50.0f, 150.0f, 1.0f);
    Sp2::PrintOutline("Press A to play sound", Color::WHITE.ToARGB(),
                      Color::BLACK.ToARGB(), false, 50.0f, 170.0f, 1.0f);
    Sp2::PrintOutline("Press B to exit to DebugRoot", Color::WHITE.ToARGB(),
                      Color::BLACK.ToARGB(), false, 50.0f, 190.0f, 1.0f);
}

/**
 * @brief Load appopriate sound group based on sound ID
 */
void Scene::LoadGroupForSound(u32 sound) {
    // Streamed audio doesn't use groups
    if (sound <= STM_SILENT) {
        return;
    }

    // Swordplay - Showdown theme (sequenced)
    else if (sound == BGM_SWF_KUMITE) {
        LoadGroup(Group_SwfKumite);
    }

    // Cycling - Road Race theme (sequenced)
    else if (sound == BGM_BIC_MAIN) {
        LoadGroup(Group_Bic);
    }

    // Jetski/Wakeboarding (they share a group)
    else if (sound >= SE_JSK_COUNT_DOWN_1 && sound <= SE_JSK_MINI_FANFARE) {
        LoadGroup(Group_Jsk);
    }

    // Frisbee Dog
    else if (sound >= SE_FLD_DOG_BARK_PREPARE &&
             sound <= SE_FLD_BALLOON_CLEAR) {
        LoadGroup(Group_Fld);
    }

    // Archery
    else if (sound >= SE_ARC_ARROW_FLY && sound <= SE_ARC_GOLDEN_ARROW_HIT) {
        LoadGroup(Group_Arc);
    }

    // Swordplay (Main group)
    // TODO: Split this up
    else if (sound >= SE_SWF_ATTACK_SUCCESS_P0 &&
             sound <= SE_SWF_IAI_CUTOBJ_CRYSTAL_TONE_10) {
        LoadGroup(Group_Swf);
    }

    // Basketball
    else if (sound >= SE_BSK_AUDIENCE_GAME_START &&
             sound <= SE_BSK_SCORE_MATCH_3PT) {
        LoadGroup(Group_Bsk);
    }

    // Table Tennis
    else if (sound >= SE_PNG_THROW_UP && sound <= SE_PNG_CAN_BOUND_LAWN_S) {
        LoadGroup(Group_Png);
    }

    // Canoeing
    else if (sound >= SE_CAN_COUNTDOWN_1 && sound <= SE_CAN_BELT_CUT) {
        LoadGroup(Group_Can);
    }

    // Bowling
    else if (sound >= SE_BWL_PLAY_NG && sound <= SE_BWL_KABEYOKE_WALL_MOVE) {
        LoadGroup(Group_Bwl);
    }

    // Cycling
    else if (sound >= SE_BIC_STOP_END && sound <= SE_BIC_NAR_EXCELLENT) {
        LoadGroup(Group_Bic);
    }

    // Plane
    else if (sound >= SE_PLN_LANDMARK_RING_GET &&
             sound <= SE_PLN_MINI_FANFARE) {
        LoadGroup(Group_Pln);
    }

    // Golf
    else if (sound >= SE_GLF_PUSH_B_OK && sound <= SE_GLF_WIND_ARROW) {
        LoadGroup(Group_Glf);
    }

    // Frisbee Golf
    else if (sound >= SE_DGL_GOAL_IN && sound <= SE_DGL_FENCE_CLOSE_END) {
        LoadGroup(Group_Dgl);
    }

    // Skydiving
    else if (sound >= SE_OMK_CATCH_COUNT && sound <= SE_OMK_TEACHER_STOP) {
        LoadGroup(Group_Omk);
    }
}

/**
 * @brief Load sound group using the audio manager
 */
void Scene::LoadGroup(EGroup id) {
    // Don't reload sound group
    if (id == mSoundGroup) {
        return;
    }

    const bool success = RPSndAudioMgr::GetInstance().loadGroup(id, 0, 0);
    CADDIE_ASSERT_EX(success, "Failed to load sound group %d", id);
}

const Color Scene::scSoundColor(255, 255, 255, 255);
const Color Scene::scSelectedSoundColor(255, 200, 0, 255);
const Color Scene::scScrollMarkerColor(255, 0, 0, 255);

const f32 Scene::scDisplayX = 300.0f;
const f32 Scene::scDisplayY = 50.0f;
const f32 Scene::scDisplayLineFeed = 20.0f;
const f32 Scene::scDisplayScale = 1.0f;

const f32 Scene::scScrollBarX = Scene::scDisplayX + 350.0f;
const f32 Scene::scScrollBarScale = 1.0f;
const f32 Scene::scScrollMarkerScale = 1.25f;
const f32 Scene::scScrollBarLineFeed = 20.0f;

} // namespace SoundTest
} // namespace caddie
