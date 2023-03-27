#include "caddieSceneCreatorEx.hpp"

#include "caddieColor.hpp"
#include "caddieDebugRootScene.hpp"
#include "caddieDebugger.hpp"
#include "caddieInputMgr.hpp"
#include "caddieSoundTestScene.hpp"

namespace caddie {

RPSysScene* SceneCreatorEx::CreateEx(ESceneID id) {
    // If the player is holding 1 + 2 + D-Up when accessing the menu scene,
    // enter the debug menu
    if (id == SCENE_TITLE) {
        if (InputMgr::GetInstance().IsHeld(InputMgr::PLAYER_1,
                                           InputMgr::BTN_1 | InputMgr::BTN_2 |
                                               InputMgr::BTN_UP)) {
            id = SCENE_DEBUG_ROOT;
        }
    }

    // Attempt to create WS2 scene
    RPSysScene* scene = createWS2Scene(id);

    // Must be a Caddie extension
    if (scene == NULL) {
        scene = CreateCaddieScene(id);
    }

    CADDIE_ASSERT_EX(scene != NULL, "Failed to create scene %d.", id);
    scene->setCreatorSceneID(mSceneID);

    return scene;
}
kmBranchMF(0x8022ec90, SceneCreatorEx, CreateEx);

RPSysScene* SceneCreatorEx::CreateCaddieScene(ESceneID id) {
    switch (id) {
    case SCENE_DEBUG_ROOT:
        return new DebugRoot::Scene();
    case SCENE_SOUND_TEST_1:
        return new SoundTest::Scene();
    }

    return NULL;
}

} // namespace caddie
