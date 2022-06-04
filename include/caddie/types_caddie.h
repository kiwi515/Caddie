#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include "caddieAssert.h"
#include "caddieMemMgr.h"
#include "caddieRuntime.h"

#include <types.h>

namespace caddie {

// kernel
struct MemManager;

// core
template <typename T> struct TLinkList;
struct TLinkListNode;
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
