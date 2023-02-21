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
class Exception;
class MemManager;

// core
class MapFile;
template <typename T> class TLinkList;
struct TLinkListNode;
struct SceneHook;
class SceneHookMgr;
template <typename T> class TStack;

// ui
class BuildInfo;
class Pane;
class PaneMgr;
class TextBox;

// math
template <typename T> class Vec2;
template <typename T> class Vec3;
template <typename T> class Vec4;

// scene/cmn
class AllSceneHook;

} // namespace caddie

#endif
