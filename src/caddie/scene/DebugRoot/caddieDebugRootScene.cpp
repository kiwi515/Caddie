#include "caddieDebugRootScene.hpp"

#include "caddieColor.hpp"
#include "caddieInputMgr.hpp"
#include "caddieSceneCreatorEx.hpp"

#include <RP/RPAudio.h>
#include <Sports2/Sp2DrawMgr.h>
#include <Sports2/Sp2Snd.h>
#include <Sports2/Sp2Util.h>
#include <revolution/OS.h>

namespace caddie {
namespace DebugRoot {
namespace {

/**
 * @brief Entry in scene selection menu
 */
struct Option {
    const char* name;
    int id;

    // TODO: Remove this
    bool enabled;
};

const Option scOptions[] = {
    // clang-format off
    {"Strap",               SceneCreatorEx::SCENE_STRAP,             false},
    {"SaveDataLoad",        SceneCreatorEx::SCENE_SAVE_DATA_LOAD,    false},
    {"Title",               SceneCreatorEx::SCENE_TITLE,             true},
    {"MiiSelect",           SceneCreatorEx::SCENE_MII_SELECT,        true},
    {"SwfScene",            SceneCreatorEx::SCENE_SWF,               false},
    {"JskScene",            SceneCreatorEx::SCENE_JSK,               false},
    {"ArcScene",            SceneCreatorEx::SCENE_ARC,               false},
    {"FldScene",            SceneCreatorEx::SCENE_FLD,               false},
    {"BskScene",            SceneCreatorEx::SCENE_BSK,               false},
    {"BwlScene",            SceneCreatorEx::SCENE_BWL,               false},
    {"CanScene",            SceneCreatorEx::SCENE_CAN,               false},
    {"PngScene",            SceneCreatorEx::SCENE_PNG,               false},
    {"WkbScene",            SceneCreatorEx::SCENE_WKB,               false},
    {"PlnScene",            SceneCreatorEx::SCENE_PLN,               false},
    {"GlfScene",            SceneCreatorEx::SCENE_GLF,               false},
    {"DglScene",            SceneCreatorEx::SCENE_DGL,               false},
    {"BicScene",            SceneCreatorEx::SCENE_BIC,               false},
    {"OmkScene",            SceneCreatorEx::SCENE_OMK,               false},
    {"DebugRoot",           SceneCreatorEx::SCENE_DEBUG_ROOT,        false},
    {"SaveDataDebug",       SceneCreatorEx::SCENE_SAVE_DATA_DEBUG,   false},
    {"ContestMiiDebug",     SceneCreatorEx::SCENE_CONTEST_MII_DEBUG, false},
    {"MessageCheck",        SceneCreatorEx::SCENE_MESSAGE_CHECK,     false},
    {"LayoutCheck",         SceneCreatorEx::SCENE_LAYOUT_CHECK,      false},
    {"LayoutCheck2",        SceneCreatorEx::SCENE_LAYOUT_CHECK_2,    false},
    {"NkjTest1",            SceneCreatorEx::SCENE_NKJ_TEST_1,        false},
    {"LayoutTest1",         SceneCreatorEx::SCENE_LAYOUT_TEST_1,     false},
    {"SoundTest1",          SceneCreatorEx::SCENE_SOUND_TEST_1,      true},
    {"CPUMii",              SceneCreatorEx::SCENE_CPU_MII,           false},
    // clang-format on
};

inline int GetNumOptions() { return ARRAY_LENGTH(scOptions); }

const int scColumnSize = 16;
const f32 scColumnWidth = 150.0f;

const f32 scDisplayX = 100.0f;
const f32 scDisplayY = 100.0f;

const f32 scLineFeed = 20.0f;

} // namespace

Scene::Scene()
    : mSelectedScene(0), mFadeTimer(scFadeTimerDefault), mNextScene(-1) {}

void Scene::Calculate() {
    // Scene transition
    if (mNextScene != -1 && --mFadeTimer < 0) {
        SceneCreatorEx::GetInstance().changeSceneAfterFade(mNextScene,
                                                           Color::WHITE);
    }

    const u32 trig = InputMgr::GetInstance().Trig(InputMgr::PLAYER_1);

    // Move cursor down
    if (trig & InputMgr::BTN_DOWN) {
        mSelectedScene++;
    }
    // Move cursor up
    else if (trig & InputMgr::BTN_UP) {
        mSelectedScene--;
    }
    // Move cursor left
    else if (trig & InputMgr::BTN_LEFT) {
        if (mSelectedScene > scColumnSize) {
            mSelectedScene -= scColumnSize;
        }
    }
    // Move cursor right
    else if (trig & InputMgr::BTN_RIGHT) {
        if (mSelectedScene < GetNumOptions() - scColumnSize) {
            mSelectedScene += scColumnSize;
        }
    }

    // Bounds check
    mSelectedScene = Min(mSelectedScene, GetNumOptions() - 1);
    mSelectedScene = Max(mSelectedScene, 0);

    // Select scene
    if (trig & InputMgr::BTN_A) {
        const Option& opt = scOptions[mSelectedScene];

        if (opt.enabled) {
            RPSndAudioMgr::startSound(SE_CMN_TITLE_GAME_SEL);
            mNextScene = opt.id;
        } else {
            RPSndAudioMgr::startSound(SE_CMN_NG_01);
        }
    }

    // Exit to title
    if (trig & InputMgr::BTN_B) {
        RPSndAudioMgr::startSound(SE_CMN_CANCEL_01);
        mNextScene = SceneCreatorEx::SCENE_TITLE;
    }
}

void Scene::UserDraw() {
    if (Sp2::DrawMgr::getDrawPass() == Sp2::DrawMgr::DrawPass_4) {
        // Divide list into columns
        int columns = GetNumOptions() / scColumnSize;
        // Overflow
        if (GetNumOptions() % scColumnSize != 0) {
            columns++;
        }

        // Display list
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < scColumnSize; j++) {
                // Item position
                const f32 x = scDisplayX + (i * scColumnWidth);
                const f32 y = scDisplayY + (j * scLineFeed);

                // 2D index -> 1D (array) index
                const int index1D = (i * scColumnSize) + j;
                if (index1D >= GetNumOptions()) {
                    break;
                }

                // Display item
                Sp2::PrintfOutline(x, y, 1.25f, Color::WHITE.ToARGB(),
                                   Color(80, 80, 80, 255).ToARGB(), false,
                                   scOptions[index1D].name);
            }
        }

        // Display cursor
        const f32 cursorCol = mSelectedScene / scColumnSize;
        const f32 cursorRow = mSelectedScene % scColumnSize;
        const f32 cursorX = scDisplayX + (cursorCol * scColumnWidth) - 15.0f;
        const f32 cursorY = scDisplayY + (cursorRow * scLineFeed);

        Sp2::Print("*", Color::WHITE.ToARGB(), false, cursorX, cursorY);
    }
}

} // namespace DebugRoot
} // namespace caddie
