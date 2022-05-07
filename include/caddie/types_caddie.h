#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include <types.h>

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
    struct Pane;
    struct TextBox;
    struct MenuOptionBase;
    struct MenuIntOption;
    struct MenuEnumOption;
    struct MenuLocalizedEnumOption;
    struct MenuActionOption;
    struct MenuBoolOption;
    struct MenuBase;

    // game/golf
    struct GolfMenu;
    struct GolfSceneHook;
}

#endif