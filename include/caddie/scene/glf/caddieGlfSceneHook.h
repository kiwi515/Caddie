#ifndef CADDIE_SCENE_GLF_SCENE_HOOK_H
#define CADDIE_SCENE_GLF_SCENE_HOOK_H
#include "types_Sp2.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Golf scene hook
 */
class GlfSceneHook {
public:
    static void OnConfigure(RPSysScene*);
    static void OnCalculate(RPSysScene*);
    static void OnUserDraw(RPSysScene*);
    static void OnExit(RPSysScene*);

    static void Apply_Hole();
    static void Apply_RepeatHole();
    static void Apply_Pin();
    static void Apply_Wind();

    static void Apply_StaticMem();
    static void Apply_GlfMain();

    static void OnGlfBallCalc(RPGlfBall*, u32, u32);
    static bool ShouldShowTutorial();
    static bool CanPlayNextHole();
    static u32 GetNumHolesPlayed();

    static GlfMenu& GetMenu();

private:
    //! @brief Golf menu
    static GlfMenu* sGlfMenu;
};

} // namespace caddie

#endif
