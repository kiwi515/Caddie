#include "caddieSceneHookMgr.h"
#include "caddieGlfSceneHook.h"
#include "ui_test.h"

namespace caddie
{
    /**
     * @brief Mod entrypoint
     */
    void main()
    {
        SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

        // Set up Golf scene hook
        hookMgr.SetHook(RPSysSceneCreator::SCENE_GLF, (SceneHook){
                GlfSceneHook::OnConfigure,
                GlfSceneHook::OnCalculate,
                GlfSceneHook::OnUserDraw,
                GlfSceneHook::OnExit
            }
        );

        // Set up UI test
        hookMgr.SetHook(RPSysSceneCreator::SCENE_TITLE, (SceneHook){
                UiTest::Configure,
                UiTest::Calculate,
                UiTest::UserDraw,
                UiTest::Exit,
            }
        );
    }
    kmBranch(0x80230fc4, main);
}