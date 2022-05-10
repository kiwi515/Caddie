#ifndef RP_SYSTEM_SCENE_CREATOR_H
#define RP_SYSTEM_SCENE_CREATOR_H
#include "types_rp.h"
#include "types_nw4r.h"

class RPSysSceneCreator
{
public:
    //! @brief RP Scene ID
    //! @wfuname
    enum ESceneID
    {
        SCENE_STRAP,
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

public:    
    static RPSysSceneCreator * getInstance() { return sInstance; }

    void changeSceneAfterFade(int id, nw4r::ut::Color *fadeColor);

private:
    static RPSysSceneCreator *sInstance;
};

#endif