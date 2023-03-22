#include "caddieSceneCreatorEx.hpp"

#include "caddieColor.hpp"
#include "caddieDebugRootScene.hpp"
#include "caddieDebugger.hpp"

namespace caddie {

RPSysScene* SceneCreatorEx::CreateEx(ESceneID id) {
    // Attempt to create WS2 scene
    RPSysScene* scene = createWS2Scene(id);

    // Must be a Caddie extension
    if (scene == NULL) {
        scene = CreateCaddieScene(id);
    }

    CADDIE_ASSERT_EX(scene != NULL, "Failed to create scene %d.", id);
    scene->setCreatorSceneID(mSceneID);

    if (id == SCENE_DEBUG_ROOT) {
        CADDIE_LOG_EX(
            "!!!\n!!!\n!!! Debug root scene created at: %08X\n!!!\n!!!", scene);
    }

    return scene;
}
kmBranchMF(0x8022ec90, SceneCreatorEx, CreateEx);

RPSysScene* SceneCreatorEx::CreateCaddieScene(ESceneID id) {
    switch (id) {
    case SCENE_DEBUG_ROOT:
        // DEBUGGER_BREAK();
        return new DebugRoot::Scene();
    }

    return NULL;
}

SceneCreatorEx::ESceneID SceneCreatorEx::GetTitleScene() const {
    // If this is from a boot, go to the debugging scene
    if (RPSysSceneMgr::getInstance().getPreviousSceneID() == SCENE_STRAP) {
        return SCENE_DEBUG_ROOT;
    }

    // Otherwise, proceed to the title screen as usual
    return SCENE_TITLE;
}
kmBranchMF(0x8022edf4, SceneCreatorEx, GetTitleScene);

} // namespace caddie
