#ifndef TYPES_CADDIE_H
#define TYPES_CADDIE_H
#include <RP/types_rp.h>
#include <Sports2/types_sp2.h>
#include <egg/types_egg.h>
#include <nw4r/types_nw4r.h>
#include <types.h>

//

#include <core/caddieAssert.h>
#include <kernel/caddieMemMgr.h>
#include <kernel/caddieRuntime.h>

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

struct Timer;

// scene/glf
struct GlfMenu;
struct GlfSceneHook;
struct GlfUtil;

} // namespace caddie

#endif
