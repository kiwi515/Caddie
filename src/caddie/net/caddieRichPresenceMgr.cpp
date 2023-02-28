#include "caddieRichPresenceMgr.hpp"

#include "BCMSG_RichPresence.hpp"
#include "caddieEmuRichPresence.hpp"
#include "caddieHashMap.hpp"
#include "caddieMessage.hpp"
#include "caddieResourceMgr.hpp"
#include "caddieRvlRichPresence.hpp"

#include <RP/RPSystem.h>
#include <Sports2/Sp2StaticMem.h>

namespace caddie {
namespace {

/**
 * @brief RPC information for a given scene + sequence
 */
struct SceneSeqRpcInfo {
    int msg;
    const char* image;
};

extern const SceneSeqRpcInfo scRpcInfo[RPSysSceneCreator::SCENE_MAX]
                                      [RPSysSceneCreator::SEQ_MAX];

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

    // Get new scene and sequence
    const int scene = RPSysSceneMgr::getInstance().getCurrentSceneID();
    const u32 seq = Sp2::StaticMem::getInstance().getSceneSeq();
    CADDIE_ASSERT_EX(scene < RPSysSceneCreator::SCENE_MAX &&
                         seq < RPSysSceneCreator::SEQ_MAX,
                     "Invalid scene(%d) or sequence(%d)", scene, seq);

    // Do not change presence if the scene is only reloading
    if (mLastSceneID == scene) {
        return;
    }

    // Get new state/image for RPC
    const SceneSeqRpcInfo& info = scRpcInfo[scene][seq];
    CADDIE_ASSERT_EX(info.msg >= 0 && info.image != NULL,
                     "Scene(%d) or sequence(%d) with no RPC info", scene, seq);
    const wchar_t* state = mMessage->GetMessage(info.msg);
    const char* largeImageKey = info.image;

    // Reflect info on Discord
    mRichPresence->SetStartTimeNow();
    mRichPresence->SetState(state);
    mRichPresence->SetLargeImageKey(largeImageKey);
    mRichPresence->UpdatePresence();
}

/**
 * @brief Scene exit callback. Scene ID is tracked to prevent RPC timer from
 * restarting when the scene is reloaded (NOT changed)
 */
void RichPresenceMgr::Exit() {
    mLastSceneID = RPSysSceneMgr::getInstance().getCurrentSceneID();
}

namespace {

const SceneSeqRpcInfo scRpcInfo[RPSysSceneCreator::SCENE_MAX]
                               [RPSysSceneCreator::SEQ_MAX] = {
                                   // clang-format off
    // SCENE_STRAP
    {
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
    },

    // SCENE_SAVE_DATA_LOAD
    {
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
    },

    // SCENE_TITLE
    {
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
    },

    // SCENE_MII_SELECT
    {
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
        {MSG_RPC_STATE_MENU, "menu"},
    },

    // SCENE_SWF
    {
        {-1, NULL},
        {MSG_RPC_STATE_SWF_SGL, "swf_sgl"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_SWF_VS, "swf_vs"},
        {MSG_RPC_STATE_SWF_PRC, "swf_prc"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_JSK
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_JSK_RNG, "jsk_rng"},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_JSK_VS, "jsk_vs"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_ARC
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_ARC, "arc"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_FLD
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_FLD, "fld"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_BSK
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_BSK_3PT, "bsk_3pt"},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_BSK_VS, "bsk_vs"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_BWL
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_BWL_STD, "bwl_std"},
        {MSG_RPC_STATE_BWL_100, "bwl_100"},
        {MSG_RPC_STATE_BWL_WAL, "bwl_wal"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_CAN
    {
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_CAN, "can_vs"},
        {MSG_RPC_STATE_CAN_VS, "can"},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_PNG
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_PNG_RET, "png_ret"},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_PNG, "png"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_WKB
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_WKB, "wkb"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_PLN
    {
        {MSG_RPC_STATE_PLN, "pln"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_PLN_VS, "pln_vs"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_GLF
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_GLF, "glf"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_DGL
    {
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_DGL, "dgl"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_BIC
    {
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_BIC_VS, "bic_vs"},
        {-1, NULL},
        {-1, NULL},
        {MSG_RPC_STATE_BIC, "bic"},
        {-1, NULL},
        {-1, NULL},
    },

    // SCENE_OMK
    {
        {-1, NULL},
        {MSG_RPC_STATE_OMK, "omk"},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
        {-1, NULL},
    },
                                   // clang-format on
};

}

} // namespace caddie
