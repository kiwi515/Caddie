#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include <types.h>

#include "caddieAssert.h"
#include "caddieDebug.h"
#include "caddieMemMgr.h"
#include "caddieAsm.h"

namespace caddie
{
    struct MenuOptionBase;
    struct MenuIntOption;
    struct MenuEnumOption;
    struct MenuActionOption;
    struct MenuBoolOption;

    struct MenuBase;
    struct GolfMenu;

    struct MemManager;

    struct SceneHook;
    struct GolfSceneHook;

    struct Timer;
    struct IGTTimer;
    struct RTATimer;
}

#endif