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
        static UNKTYPE * OnInit(UNKTYPE *);
        static UNKTYPE * OnFrame(UNKTYPE *);

    private:
        static IGTTimer sIGTTimer;
    };
}

#endif