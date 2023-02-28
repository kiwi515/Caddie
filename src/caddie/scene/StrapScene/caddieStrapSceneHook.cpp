#include "caddieColor.hpp"
#include "caddieStrapSceneHook.hpp"

#include <RP/RPSystem.h>

namespace caddie {

/**
 * @brief Strap scene calculate callback
 *
 * @param scene Current scene
 */
void StrapSceneHook::OnCalculate(RPSysScene* scene) {
    // Load title screen as soon as the resources are done loading
    if (scene->isTaskAsyncFinish()) {
        RPSysSceneCreator::getInstance().changeSceneAfterFade(
            RPSysSceneCreator::SCENE_SAVE_DATA_LOAD, Color(0, 0, 0, 0));
    }
}

} // namespace caddie
