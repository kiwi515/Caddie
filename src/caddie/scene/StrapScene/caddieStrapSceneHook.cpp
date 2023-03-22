#include "caddieStrapSceneHook.hpp"

#include "caddieColor.hpp"
#include "caddieSceneCreatorEx.hpp"

#include <RP/RPSystem.h>

namespace caddie {
namespace Strap {

/**
 * @brief Strap scene calculate callback
 *
 * @param scene Current scene
 */
void SceneHook::OnCalculate(RPSysScene* scene) {
    // Load title screen as soon as the resources are done loading
    if (scene->isTaskAsyncFinish()) {
        SceneCreatorEx::GetInstance().changeSceneAfterFade(
            SceneCreatorEx::SCENE_SAVE_DATA_LOAD, Color(0, 0, 0, 0));
    }
}

} // namespace Strap
} // namespace caddie
