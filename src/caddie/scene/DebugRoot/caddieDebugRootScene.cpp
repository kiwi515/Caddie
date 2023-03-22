#include "caddieDebugRootScene.hpp"

#include "caddieColor.hpp"

#include <Sports2/Sp2DrawMgr.h>
#include <Sports2/Sp2Util.h>

namespace caddie {
namespace DebugRoot {

void Scene::UserDraw() {
    if (Sp2::DrawMgr::getDrawPass() == Sp2::DrawMgr::DrawPass_4) {
        Sp2::Printf(100.0f, 100.0f, 2.0f, Color().ToARGB(), true,
                    "DebugRoot Test");
    }
}

} // namespace DebugRoot
} // namespace caddie
