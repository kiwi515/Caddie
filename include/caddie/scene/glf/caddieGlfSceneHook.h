#ifndef CADDIE_SCENE_GLF_SCENE_HOOK_H
#define CADDIE_SCENE_GLF_SCENE_HOOK_H
#include "types_caddie.h"
#include "types_RP.h"

namespace caddie
{
    /**
     * @brief Golf scene hook
     */
    class GlfSceneHook
    {
    public:
        static void OnConfigure(RPSysScene *);
        static void OnCalculate(RPSysScene *);
        static void OnUserDraw(RPSysScene *);
        static void OnExit(RPSysScene *);
        static GlfMenu* GetMenu();

    private:
        static GlfMenu* sGlfMenu;
    };
}

#endif