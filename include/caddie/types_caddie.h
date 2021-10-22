#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include <types.h>

#define ARRAY_COUNT(x) (sizeof((x)) / sizeof((x[0])))

#include "caddieAssert.h"
#include "caddieDebug.h"
#include "caddieMemMgr.h"
#include "caddieAsm.h"

namespace caddie
{
    // kernel
    struct MemManager;

    // core
    template <typename T, int ofs> struct TLinkList;
    struct TLinkListNode;
    struct Timer;
    struct IGTTimer;
    struct RTATimer;
    struct SceneHook;

    // ui
    struct MenuOptionBase;
    struct MenuIntOption;
    struct MenuEnumOption;
    struct MenuActionOption;
    struct MenuBoolOption;
    struct MenuBase;

    // game/golf
    struct GolfMenu;
    struct GolfSceneHook;
}

#endif