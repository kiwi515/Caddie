#include "caddieGlfPostMenu.h"

#include "caddieGlfMenu.h"
#include "caddieGlfMessage.h"
#include "caddieGlfPostMenu.h"
#include "caddieGlfSceneHook.h"
#include "caddieGlfUtil.h"
#include "caddieInputMgr.h"
#include "caddieMenuMgr.h"

#include <RPGraphics/RPGrpRenderer.h>
#include <RevoSDK/MTX.h>
#include <Sports2/Scene/Glf/RPGlfBall.h>
#include <Sports2/Scene/Glf/RPGlfClub.h>
#include <Sports2/Scene/Glf/RPGlfClubManager.h>
#include <Sports2/Scene/Glf/RPGlfFieldManager.h>
#include <Sports2/Scene/Glf/RPGlfPlayerManager.h>
#include <Sports2/Scene/Glf/RPGlfSimManager.h>
#include <Sports2/Scene/Glf/RPGlfUtility.h>
#include <Sports2/Scene/Glf/Sp2GlfConfig.h>
#include <Sports2/Scene/Glf/Sp2GlfDefine.h>
#include <Sports2/Scene/Glf/Sp2GlfMain.h>
#include <Sports2/Scene/Glf/Sp2GlfSequenceMgr.h>
#include <Sports2/Sp2StaticMem.h>
#include <Sports2/Sp2Util.h>
#include <egg/gfx.h>
#include <nw4r/ut.h>

namespace caddie {

GlfPostMenu::GlfPostMenu()
    : MenuBase("PostMenu", sMenuPosX, sMenuPosY),
      mNextShot("Next Shot", Action_NextShot, this),
      mTryAgain("Try Again", Action_TryAgain, this) {

    // Build root page
    GetRootPage().AppendOption(&mNextShot);
    GetRootPage().AppendOption(&mTryAgain);

    OSReport("MENU ADDR: %p\n", this);
}

GlfPostMenu::~GlfPostMenu() {}

void GlfPostMenu::Action_NextShot(void* menu) {
    CADDIE_ASSERT(menu != NULL);
    GlfPostMenu* thisx = reinterpret_cast<GlfPostMenu*>(menu);

    Sp2::Glf::SequenceMgr::getInstance().GetSequenceMain()->NextShot();
    MenuMgr::GetInstance().SetVisible(false);
    MenuMgr::GetInstance().CloseMenu();

    ChangePhase();
}

void GlfPostMenu::Action_TryAgain(void* menu) {
    CADDIE_ASSERT(menu != NULL);
    GlfPostMenu* thisx = reinterpret_cast<GlfPostMenu*>(menu);

    MenuMgr::GetInstance().SetVisible(false);
    MenuMgr::GetInstance().CloseMenu();

    ChangePhase();
}

void GlfPostMenu::ChangePhase() {
    RPGlfPlayer& player = RPGlfPlayerManager::GetInstance().GetCurrentPlayer();

    Sp2::Glf::SequenceMain* pMainSeq =
        Sp2::Glf::SequenceMgr::getInstance().GetSequenceMain();
    CADDIE_ASSERT(pMainSeq);

    if (player.GetWord0x44() == 2) {
        pMainSeq->CupIn.Enter();
    } else {
        pMainSeq->BallStop.Enter();
    }
}

const f32 GlfPostMenu::sMenuPosX = 275.0f;
const f32 GlfPostMenu::sMenuPosY = 200.0f;

} // namespace caddie
