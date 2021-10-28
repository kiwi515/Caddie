#ifndef CADDIE_CORE_SCENE_HOOK_H
#define CADDIE_CORE_SCENE_HOOK_H
#include "types_caddie.h"
#include "types_egg.h"

namespace caddie
{
    class SceneHook
    {
    public:
        static UNKTYPE * OnInit(UNKTYPE *);
        static UNKTYPE * OnFrame(UNKTYPE *);
        static bool OnExit(bool);

    private:

    };
}

#endif