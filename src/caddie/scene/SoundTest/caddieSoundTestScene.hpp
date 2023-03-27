#ifndef CADDIE_SCENE_SOUND_TEST_H
#define CADDIE_SCENE_SOUND_TEST_H
#include "caddieColor.hpp"
#include "types_caddie.hpp"

#include <RP/RPSystem.h>

namespace caddie {
namespace SoundTest {

class Scene : public RPSysScene {
public:
    Scene();
    virtual ~Scene() {}

    virtual void Calculate();
    virtual void UserDraw();

private:
    static u32 GetNumSound();
    static u32 GetMaxSoundID();

    void ResetBtnRepeat() { mBtnRepeatTimer = scRepeatTimerDefault; }

    u32 GetDisplayBottomSnd() const {
        return mDisplayTopSnd + scNumDisplay - 1;
    }

    void CursorDown(u32 num) {
        mSelectedSnd = Min<int>(mSelectedSnd + num, GetMaxSoundID());
        ResetBtnRepeat();
    }

    void CursorUp(u32 num) {
        mSelectedSnd = Max<int>(mSelectedSnd - num, 0);
        ResetBtnRepeat();
    }

    void DisplayDown(u32 num) {
        mDisplayTopSnd =
            Min<int>(mDisplayTopSnd + num, GetNumSound() - scNumDisplay);
    }

    void DisplayUp(u32 num) {
        mDisplayTopSnd = Max<int>(mDisplayTopSnd - num, 0);
    }

    void DrawList();
    void DrawScroll();
    void DrawControls();

private:
    int mSelectedSnd;
    int mDisplayTopSnd;
    int mBtnRepeatTimer;
    u32 mHeldLastFrame;

    static const int scRepeatTimerDefault = 5;

    static const Color scSoundColor;
    static const Color scSelectedSoundColor;
    static const Color scScrollMarkerColor;

    static const char* scSoundNames[];

    static const u32 scNumDisplay = 20;
    static const f32 scDisplayX;
    static const f32 scDisplayY;
    static const f32 scDisplayLineFeed;
    static const f32 scDisplayScale;

    static const u32 scNumScrollBar = 20;
    static const f32 scScrollBarX;
    static const f32 scScrollBarScale;
    static const f32 scScrollMarkerScale;
    static const f32 scScrollBarLineFeed;
};

} // namespace SoundTest
} // namespace caddie

#endif
