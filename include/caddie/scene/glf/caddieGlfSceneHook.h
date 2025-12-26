#ifndef CADDIE_SCENE_GLF_SCENE_HOOK_H
#define CADDIE_SCENE_GLF_SCENE_HOOK_H

#include "caddieTimer.h"

#include "types_caddie.h"

#include <nw4r/math.h>

namespace caddie {

class GlfMenu;
class GlfPostMenu;

/**
 * @brief Golf scene hook
 */
class GlfSceneHook {
public:
    static void OnConfigure(RPSysScene*);
    static void OnCalculate(RPSysScene*);
    static void OnExit(RPSysScene*);
    static void OnUserDraw(RPSysScene*);

    static void Apply_Hole();
    static void Apply_RepeatHole();
    static void Apply_Pin();
    static void Apply_Wind();

    static void Apply_StaticMem();
    static void Apply_GlfConfig();

    static void OnGlfBallCalc(RPGlfBall*, u32, u32);
    static void OnPausedSeqMgrCalc();
    static void OnNextShot();

    static bool ShouldShowTutorial();
    static bool CanPlayNextHole();
    static u32 GetNumHolesPlayed();

    static GlfMenu& GetMenu();
    static GlfPostMenu& GetPostMenu();

    static void DrawReplaySphere();
    static void DrawPutterGuide(const nw4r::math::VEC3* pPoints, u16 num,
                                GXColor color, u8 width);

private:
    static GlfMenu* sGlfMenu;
    static GlfPostMenu* sGlfPostMenu;

    static bool sDidStopShot;

    static Timer* sTimer;
};

} // namespace caddie

#endif
