#ifndef RP_SYSTEM_SCENE_CREATOR_H
#define RP_SYSTEM_SCENE_CREATOR_H
#include "types_nw4r.h"
#include "types_rp.h"

#include <egg/core.h>

class RPSysSceneCreator : public EGG::SceneCreator {
public:
    //! @brief RP Scene ID
    //! @wfuname
    enum ESceneID {
        SCENE_SHARED = -1,

        SCENE_STRAP = 0,
        SCENE_SAVE_DATA_LOAD,
        SCENE_TITLE,
        SCENE_MII_SELECT,

        SCENE_SWF,
        SCENE_JSK,
        SCENE_ARC,
        SCENE_FLD,
        SCENE_BSK,
        SCENE_BWL,
        SCENE_CAN,
        SCENE_PNG,
        SCENE_WKB,
        SCENE_PLN,
        SCENE_GLF,
        SCENE_DGL,
        SCENE_BIC,
        SCENE_OMK,

        SCENE_DEBUG_ROOT,
        SCENE_SAVE_DATA_DEBUG,
        SCENE_CONTEST_MII_DEBUG,
        SCENE_MESSAGE_CHECK,
        SCENE_LAYOUT_CHECK,
        SCENE_LAYOUT_CHECK_2,
        SCENE_NKJ_TEST_1,
        SCENE_LAYOUT_TEST_1,
        SCENE_SOUND_TEST_1,
        SCENE_CPU_MII,

        SCENE_MAX
    };

    //! Sequence ID (WS2)
    enum SeqID {
        SEQ_SWF_VS = 5,
        SEQ_SWF_PRC = 6,
        SEQ_SWF_SGL = 1,

        SEQ_JSK_RNG = 2,
        SEQ_JSK_VS = 5,

        SEQ_ARC = 2,

        SEQ_FLD = 2,

        SEQ_BSK_3PT = 2,
        SEQ_BSK_VS = 5,

        SEQ_BWL_STD = 2,
        SEQ_BWL_100 = 3,
        SEQ_BWL_WAL = 4,

        SEQ_CAN = 8,
        SEQ_CAN_VS = 7,

        SEQ_PNG = 5,
        SEQ_PNG_RET = 2,

        SEQ_WKB = 2,

        SEQ_PLN = 0,
        SEQ_PLN_VS = 5,

        SEQ_GLF = 2,

        SEQ_DGL = 2,

        SEQ_BIC = 8,
        SEQ_BIC_VS = 5,

        SEQ_OMK = 1,

        // NOTE: Adjust based on other values. The sequence IDs seem arbitrary.
        // Maybe a lot of cut content?
        SEQ_MAX = 11
    };

public:
    static RPSysSceneCreator& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    virtual EGG::Scene* create(s32);
    virtual void destroy(s32);

    void changeSceneAfterFade(int id, nw4r::ut::Color fadeColor);

protected:
    RPSysSceneCreator();
    virtual ~RPSysSceneCreator();

    RPSysScene* createWS2Scene(s32);

protected:
    EGG::Heap* mParentHeap; // at 0x4
    s32 mSceneID;           // at 0x8

    static RPSysSceneCreator* sInstance;
};

#endif
