#include "caddieRichPresenceMgr.hpp"

#include "BCMSG_RichPresence.hpp"
#include "caddieEmuRichPresence.hpp"
#include "caddieHashMap.hpp"
#include "caddieMessage.hpp"
#include "caddieResourceMgr.hpp"
#include "caddieRvlRichPresence.hpp"
#include "caddieSceneCreatorEx.hpp"

#include <RP/RPSystem.h>
#include <Sports2/Sp2StaticMem.h>

namespace caddie {
namespace {

/**
 * @brief RPC information for a given scene + sequence
 */
struct SceneSeqRpcInfo {
    int scene;
    int seq;
    int msg;
    const char* image;
};

extern const SceneSeqRpcInfo scRpcInfo[];

const SceneSeqRpcInfo* GetRpcInfo(int scene, int seq);

} // namespace

const char* RichPresenceMgr::scCaddieAppId = "1078748945783734282";

RichPresenceMgr::RichPresenceMgr()
    : mRichPresence(NULL), mMessage(NULL), mLastSceneID(-1) {
    // Load BCMSG
    mMessage =
        ResourceMgr::GetInstance().LoadMessage("US/Message/RichPresence.bcmsg");
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

    // Scene IDs
    RPSysSceneMgr& sceneMgr = RPSysSceneMgr::getInstance();
    const int scene = sceneMgr.getCurrentSceneID();
    const int lastScene = sceneMgr.getPreviousSceneID();

    // Do not change presence if the scene is only reloading
    if (lastScene == scene) {
        return;
    }

    // Sequnce ID
    Sp2::StaticMem& staticMem = Sp2::StaticMem::getInstance();
    const int seq = staticMem.getSceneSeq();

    CADDIE_ASSERT_EX(scene < SceneCreatorEx::SCENE_MAX &&
                         seq < SceneCreatorEx::SEQ_MAX,
                     "Invalid scene(%d) or sequence(%d)", scene, seq);

    // Get new state/image for RPC
    const SceneSeqRpcInfo* info = GetRpcInfo(scene, seq);

    // Not finding RPC info is not a fatal error, so we just ignore it
    if (info == NULL) {
        CADDIE_LOG_EX("Failed to get RPC info! Scene:%d, Sequence:%d", scene,
                      seq);
        return;
    }

    const wchar_t* state = mMessage->GetMessage(info->msg);
    const char* largeImageKey = info->image;

    // Reflect info on Discord
    mRichPresence->SetStartTimeNow();
    mRichPresence->SetState(state);
    mRichPresence->SetLargeImageKey(largeImageKey);
    mRichPresence->UpdatePresence();
}

namespace {

const SceneSeqRpcInfo scRpcInfo[] = {
    // clang-format off

    // System scenes
    {SceneCreatorEx::SCENE_STRAP,          -1, MSG_RPC_STATE_MENU, "menu"},
    {SceneCreatorEx::SCENE_SAVE_DATA_LOAD, -1, MSG_RPC_STATE_MENU, "menu"},
    {SceneCreatorEx::SCENE_TITLE,          -1, MSG_RPC_STATE_MENU, "menu"},
    {SceneCreatorEx::SCENE_MII_SELECT,     -1, MSG_RPC_STATE_MENU, "menu"},

    // Swordplay
    {SceneCreatorEx::SCENE_SWF, SceneCreatorEx::SEQ_SWF_SGL, MSG_RPC_STATE_SWF_SGL, "swf_sgl"},
    {SceneCreatorEx::SCENE_SWF, SceneCreatorEx::SEQ_SWF_VS,  MSG_RPC_STATE_SWF_VS,  "swf_vs"},
    {SceneCreatorEx::SCENE_SWF, SceneCreatorEx::SEQ_SWF_PRC, MSG_RPC_STATE_SWF_PRC, "swf_prc"},

    // Power Cruising
    {SceneCreatorEx::SCENE_JSK, SceneCreatorEx::SEQ_JSK_RNG, MSG_RPC_STATE_JSK_RNG, "jsk_rng"},
    {SceneCreatorEx::SCENE_JSK, SceneCreatorEx::SEQ_JSK_VS,  MSG_RPC_STATE_JSK_VS,  "jsk_vs"},

    // Archery
    {SceneCreatorEx::SCENE_ARC, SceneCreatorEx::SEQ_ARC, MSG_RPC_STATE_ARC, "arc"},

    // Frisbee Dog
    {SceneCreatorEx::SCENE_FLD, SceneCreatorEx::SEQ_FLD, MSG_RPC_STATE_FLD, "fld"},

    // Basketball
    {SceneCreatorEx::SCENE_BSK, SceneCreatorEx::SEQ_BSK_3PT, MSG_RPC_STATE_BSK_3PT, "bsk_3pt"},
    {SceneCreatorEx::SCENE_BSK, SceneCreatorEx::SEQ_BSK_VS,  MSG_RPC_STATE_BSK_VS,  "bsk_vs"},

    // Bowling
    {SceneCreatorEx::SCENE_BWL, SceneCreatorEx::SEQ_BWL_STD, MSG_RPC_STATE_BWL_STD, "bwl_std"},
    {SceneCreatorEx::SCENE_BWL, SceneCreatorEx::SEQ_BWL_100, MSG_RPC_STATE_BWL_100, "bwl_100"},
    {SceneCreatorEx::SCENE_BWL, SceneCreatorEx::SEQ_BWL_WAL, MSG_RPC_STATE_BWL_WAL, "bwl_wal"},

    // Canoeing
    {SceneCreatorEx::SCENE_CAN, SceneCreatorEx::SEQ_CAN_VS, MSG_RPC_STATE_CAN_VS, "can_vs"},
    {SceneCreatorEx::SCENE_CAN, SceneCreatorEx::SEQ_CAN,    MSG_RPC_STATE_CAN,    "can"},

    // Table Tennis
    {SceneCreatorEx::SCENE_PNG, SceneCreatorEx::SEQ_PNG_RET, MSG_RPC_STATE_PNG_RET, "png_ret"},
    {SceneCreatorEx::SCENE_PNG, SceneCreatorEx::SEQ_PNG,     MSG_RPC_STATE_PNG,     "png"},

    // Wakeboarding
    {SceneCreatorEx::SCENE_WKB, SceneCreatorEx::SEQ_WKB, MSG_RPC_STATE_WKB, "wkb"},

    // Island Flyover/Dogfight
    {SceneCreatorEx::SCENE_PLN, SceneCreatorEx::SEQ_PLN,    MSG_RPC_STATE_PLN,    "pln"},
    {SceneCreatorEx::SCENE_PLN, SceneCreatorEx::SEQ_PLN_VS, MSG_RPC_STATE_PLN_VS, "pln_vs"},

    // Golf
    {SceneCreatorEx::SCENE_GLF, SceneCreatorEx::SEQ_GLF, MSG_RPC_STATE_GLF, "glf"},

    // Frisbee Golf
    {SceneCreatorEx::SCENE_DGL, SceneCreatorEx::SEQ_DGL, MSG_RPC_STATE_DGL, "dgl"},

    // Cycling
    {SceneCreatorEx::SCENE_BIC, SceneCreatorEx::SEQ_BIC_VS, MSG_RPC_STATE_BIC_VS, "bic_vs"},
    {SceneCreatorEx::SCENE_BIC, SceneCreatorEx::SEQ_BIC,    MSG_RPC_STATE_BIC,    "bic"},

    // Skydiving
    {SceneCreatorEx::SCENE_OMK, SceneCreatorEx::SEQ_OMK, MSG_RPC_STATE_OMK, "omk"},

    // clang-format on
};

/**
 * @brief Get RPC info for a given scene + sequence
 */
const SceneSeqRpcInfo* GetRpcInfo(int scene, int seq) {
    for (int i = 0; i < ARRAY_LENGTH(scRpcInfo); i++) {
        const SceneSeqRpcInfo* info = &scRpcInfo[i];

        // Scene matches
        if (info->scene == scene) {
            // Sequence matches (or RPC info applies to all sequences)
            if (info->seq == seq || info->seq == -1) {
                return info;
            }
        }
    }

    return NULL;
}

} // namespace

} // namespace caddie
