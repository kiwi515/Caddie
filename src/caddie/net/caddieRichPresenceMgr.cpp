#include "caddieRichPresenceMgr.h"

#include "BCMSG_RichPresence.h"
#include "caddieEmuRichPresence.h"
#include "caddieMessage.h"
#include "caddieResourceMgr.h"
#include "caddieRvlRichPresence.h"

#include <RP/RPSystem.h>
#include <Sports2/Sp2StaticMem.h>

namespace caddie {

RichPresenceMgr::RichPresenceMgr() : mRichPresence(NULL), mMessage(NULL) {
    // Load BCMSG
    mMessage = ResourceMgr::GetInstance().LoadStaticMessage(
        "US/Message/RichPresence.bcmsg");
    CADDIE_ASSERT(mMessage != NULL);

    // Try setting up Dolphin Emulator rich presence (assume platform is EMU)
    mRichPresence = new EmuRichPresence(scCaddieAppId);
    CADDIE_ASSERT(mRichPresence != NULL);
    if (mRichPresence->IsConnected()) {
        CADDIE_LOG("Dolphin rich presence successfully set up");
        return;
    }

    // EmuRichPresence failed, lets try the console version
    mRichPresence = new RvlRichPresence(scCaddieAppId);
    CADDIE_ASSERT(mRichPresence != NULL);
    if (mRichPresence->IsConnected()) {
        CADDIE_LOG("Console rich presence successfully set up");
        return;
    }

    CADDIE_LOG("Could not set up rich presence!");
}

RichPresenceMgr::~RichPresenceMgr() { delete mRichPresence; }

/**
 * @brief Scene configure callback. Sets up presence info based on the new scene
 */
void RichPresenceMgr::Configure() {
    CADDIE_ASSERT(mMessage != NULL);

    // Rich presence unsupported
    if (mRichPresence == NULL) {
        return;
    }

    const s32 scene = RPSysSceneMgr::getInstance().getCurrentSceneID();
    const u32 seq = Sp2::StaticMem::getInstance().getSceneSeq();

    // Get RPC info based on the scene + sequence (game mode)
    const wchar_t* state = L"";
    const char* largeImageKey = "";

    switch (scene) {
    /**
     * Menu scenes
     */
    case RPSysSceneCreator::SCENE_STRAP:
    case RPSysSceneCreator::SCENE_SAVE_DATA_LOAD:
    case RPSysSceneCreator::SCENE_TITLE:
    case RPSysSceneCreator::SCENE_MII_SELECT:
        state = mMessage->GetMessage(MSG_RPC_STATE_MENU);
        largeImageKey = "menu";
        break;

    /**
     * Swordplay
     */
    case RPSysSceneCreator::SCENE_SWF:
        switch (seq) {
        case RPSysSceneCreator::SEQ_SWF_VS:
            state = mMessage->GetMessage(MSG_RPC_STATE_SWF_VS);
            largeImageKey = "swf_vs";
            break;
        case RPSysSceneCreator::SEQ_SWF_PRC:
            state = mMessage->GetMessage(MSG_RPC_STATE_SWF_PRC);
            largeImageKey = "swf_prc";
            break;
        case RPSysSceneCreator::SEQ_SWF_SGL:
            state = mMessage->GetMessage(MSG_RPC_STATE_SWF_SGL);
            largeImageKey = "swf_sgl";
            break;
        }
        break;

    /**
     * Power Cruising
     */
    case RPSysSceneCreator::SCENE_JSK:
        switch (seq) {
        case RPSysSceneCreator::SEQ_JSK_RNG:
            state = mMessage->GetMessage(MSG_RPC_STATE_JSK_RNG);
            largeImageKey = "jsk_rng";
            break;
        case RPSysSceneCreator::SEQ_JSK_VS:
            state = mMessage->GetMessage(MSG_RPC_STATE_JSK_VS);
            largeImageKey = "jsk_vs";
            break;
        }
        break;

    /**
     * Archery
     */
    case RPSysSceneCreator::SCENE_ARC:
        switch (seq) {
        case RPSysSceneCreator::SEQ_ARC:
            state = mMessage->GetMessage(MSG_RPC_STATE_ARC);
            largeImageKey = "arc";
            break;
        }
        break;

    /**
     * Frisbee Dog
     */
    case RPSysSceneCreator::SCENE_FLD:
        switch (seq) {
        case RPSysSceneCreator::SEQ_FLD:
            state = mMessage->GetMessage(MSG_RPC_STATE_FLD);
            largeImageKey = "fld";
            break;
        }
        break;

    /**
     * Basketball
     */
    case RPSysSceneCreator::SCENE_BSK:
        switch (seq) {
        case RPSysSceneCreator::SEQ_BSK_3PT:
            state = mMessage->GetMessage(MSG_RPC_STATE_BSK_3PT);
            largeImageKey = "bsk_3pt";
            break;
        case RPSysSceneCreator::SEQ_BSK_VS:
            state = mMessage->GetMessage(MSG_RPC_STATE_BSK_VS);
            largeImageKey = "bsk_vs";
            break;
        }
        break;

    /**
     * Bowling
     */
    case RPSysSceneCreator::SCENE_BWL:
        switch (seq) {
        case RPSysSceneCreator::SEQ_BWL_STD:
            state = mMessage->GetMessage(MSG_RPC_STATE_BWL_STD);
            largeImageKey = "bwl_std";
            break;
        case RPSysSceneCreator::SEQ_BWL_100:
            state = mMessage->GetMessage(MSG_RPC_STATE_BWL_100);
            largeImageKey = "bwl_100";
            break;
        case RPSysSceneCreator::SEQ_BWL_WAL:
            state = mMessage->GetMessage(MSG_RPC_STATE_BWL_WAL);
            largeImageKey = "bwl_wal";
            break;
        }
        break;

    /**
     * Canoeing
     */
    case RPSysSceneCreator::SCENE_CAN:
        switch (seq) {
        case RPSysSceneCreator::SEQ_CAN:
            state = mMessage->GetMessage(MSG_RPC_STATE_CAN);
            largeImageKey = "can";
            break;
        case RPSysSceneCreator::SEQ_CAN_VS:
            state = mMessage->GetMessage(MSG_RPC_STATE_CAN_VS);
            largeImageKey = "can_vs";
            break;
        }
        break;

    /**
     * Table Tennis
     */
    case RPSysSceneCreator::SCENE_PNG:
        switch (seq) {
        case RPSysSceneCreator::SEQ_PNG:
            state = mMessage->GetMessage(MSG_RPC_STATE_PNG);
            largeImageKey = "png";
            break;
        case RPSysSceneCreator::SEQ_PNG_RET:
            state = mMessage->GetMessage(MSG_RPC_STATE_PNG_RET);
            largeImageKey = "png_ret";
            break;
        }
        break;

    /**
     * Wakeboarding
     */
    case RPSysSceneCreator::SCENE_WKB:
        switch (seq) {
        case RPSysSceneCreator::SEQ_WKB:
            state = mMessage->GetMessage(MSG_RPC_STATE_WKB);
            largeImageKey = "wkb";
            break;
        }
        break;

    /**
     * Airplane
     */
    case RPSysSceneCreator::SCENE_PLN:
        switch (seq) {
        case RPSysSceneCreator::SEQ_PLN:
            state = mMessage->GetMessage(MSG_RPC_STATE_PLN);
            largeImageKey = "pln";
            break;
        case RPSysSceneCreator::SEQ_PLN_VS:
            state = mMessage->GetMessage(MSG_RPC_STATE_PLN_VS);
            largeImageKey = "pln_vs";
            break;
        }
        break;

    /**
     * Golf
     */
    case RPSysSceneCreator::SCENE_GLF:
        switch (seq) {
        case RPSysSceneCreator::SEQ_GLF:
            state = mMessage->GetMessage(MSG_RPC_STATE_GLF);
            largeImageKey = "glf";
            break;
        }
        break;

    /**
     * Frisbee Golf
     */
    case RPSysSceneCreator::SCENE_DGL:
        switch (seq) {
        case RPSysSceneCreator::SEQ_DGL:
            state = mMessage->GetMessage(MSG_RPC_STATE_DGL);
            largeImageKey = "dgl";
            break;
        }
        break;

    /**
     * Cycling
     */
    case RPSysSceneCreator::SCENE_BIC:
        switch (seq) {
        case RPSysSceneCreator::SEQ_BIC:
            state = mMessage->GetMessage(MSG_RPC_STATE_BIC);
            largeImageKey = "bic";
            break;
        case RPSysSceneCreator::SEQ_BIC_VS:
            state = mMessage->GetMessage(MSG_RPC_STATE_BIC_VS);
            largeImageKey = "bic_vs";
            break;
        }
        break;

    /**
     * Skydiving
     */
    case RPSysSceneCreator::SCENE_OMK:
        switch (seq) {
        case RPSysSceneCreator::SEQ_OMK:
            state = mMessage->GetMessage(MSG_RPC_STATE_OMK);
            largeImageKey = "omk";
            break;
        }
        break;
    }

    // Reflect info on Discord
    mRichPresence->SetStartTimeNow();
    mRichPresence->SetState(state);
    mRichPresence->SetLargeImageKey(largeImageKey);
    mRichPresence->UpdatePresence();
}

const char* RichPresenceMgr::scCaddieAppId = "1078748945783734282";

} // namespace caddie
