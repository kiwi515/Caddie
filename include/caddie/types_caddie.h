#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include "caddieAsm.h"
#include "caddieAssert.h"
#include "caddieDebug.h"
#include "caddieMemMgr.h"

#include <types.h>

namespace caddie {

// kernel
struct MemManager;

// core
template <typename T> struct TLinkList;
struct TLinkListNode;
struct Timer;
struct IGTTimer;
struct RTATimer;
struct SceneHook;

// ui
struct Pane;
struct TextBox;
struct IMenuOption;
struct MenuPage;
struct MenuBase;
struct MenuMgr;

// scene/glf
struct GlfMenu;
struct GlfSceneHook;

} // namespace caddie

#endif
