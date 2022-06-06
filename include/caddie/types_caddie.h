#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include "caddieAssert.h"
#include "caddieMemMgr.h"
#include "caddieRuntime.h"

#include <types.h>

namespace caddie {

// kernel
struct Exception;
struct MemManager;

// core
struct MapFile;
template <typename T> struct TLinkList;
struct TLinkListNode;
struct SceneHook;
struct SceneHookMgr;
template <typename T> struct TStack;

// ui
struct MenuBase;
struct MenuMgr;
struct IMenuOption;
struct MenuIntOption;
struct MenuBoolOption;
struct MenuEnumOption;
struct MenuActionOption;
struct MenuPage;
struct BuildInfo;
struct Pane;
struct TextBox;

// scene/glf
struct GlfMenu;
struct GlfSceneHook;
struct GlfUtil;

} // namespace caddie

#endif
