#include "caddieCmnAllSceneHook.h"

#include "caddieBuildInfo.h"
#include "caddieDebugger.h"
#include "caddieInputMgr.h"
#include "caddieResourceMgr.h"
#include "caddieWideTextWriter.h"

namespace caddie {

/**
 * @brief All scene configure (enter) callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnConfigure(RPSysScene* scene) {
#pragma unused(scene)
    if (sBuildInfo == NULL) {
        sBuildInfo = new BuildInfo();
        CADDIE_ASSERT(sBuildInfo != NULL);
    }

    if (sTestMessage == NULL) {
        void* bin = ResourceMgr::GetInstance().LoadStaticFromDVD(
            "US/Message/TestMessage.cmsg");
        sTestMessage = new Message(bin);
        DEBUGGER_PRINT_VAR("%08X", sTestMessage);
    }
}

/**
 * @brief All scene calculate callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnCalculate(RPSysScene* scene) {
#pragma unused(scene)
    InputMgr::GetInstance().Calculate();
}

/**
 * @brief All scene user draw callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnUserDraw(RPSysScene* scene) {
#pragma unused(scene)
    CADDIE_ASSERT(sBuildInfo != NULL);
    sBuildInfo->UserDraw();
    sBuildInfo->DebugDraw();

    WideTextWriter::GetInstance().Printf(0.0f, 0.0f,
                                         sTestMessage->GetMessage(0));
}

/**
 * @brief All scene exit callback
 *
 * @param scene Current scene
 */
void AllSceneHook::OnExit(RPSysScene* scene) {
#pragma unused(scene)
    ResourceMgr::GetInstance().ClearSceneCache();
}

BuildInfo* AllSceneHook::sBuildInfo = NULL;
Message* AllSceneHook::sTestMessage = NULL;

} // namespace caddie
