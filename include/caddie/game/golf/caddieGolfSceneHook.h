#ifndef CADDIE_GAME_GOLF_SCENE_HOOK_H
#define CADDIE_GAME_GOLF_SCENE_HOOK_H
#include "types_caddie.h"
#include "types_egg.h"

#include "caddieIGTTimer.h"

namespace caddie
{
    class GolfSceneHook
    {
    public:
        static void OnInit();
        static void OnFrame();

        static void OnUpdateHole();

    private:
    };
}

#endif