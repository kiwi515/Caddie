#ifndef CADDIE_SCENE_CMN_GLOBAL_SCENE_HOOK_H
#define CADDIE_SCENE_CMN_GLOBAL_SCENE_HOOK_H
#include "types_RP.h"
#include "types_caddie.h"

namespace caddie {

/**
 * @brief Global scene hook
 */
class GlobalSceneHook {
  public:
    static void OnConfigure(RPSysScene*);
    static void OnCalculate(RPSysScene*);
    static void OnUserDraw(RPSysScene*);
    static void OnExit(RPSysScene*);

  private:
    //! @brief Build info text
    static BuildInfo* sBuildInfo;
};

} // namespace caddie

#endif
