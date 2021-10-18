#ifndef RP_SYSTEM_SCENE_CREATOR_H
#define RP_SYSTEM_SCENE_CREATOR_H
#include "types_rp.h"
#include "types_nw4r.h"

#include "caddieAssert.h"

class RPSysSceneCreator
{
public:
    inline static RPSysSceneCreator * getInstance()
    {
        return sInstance;
    }

    void changeSceneAfterFade(int id, nw4r::ut::Color *fadeColor);

private:
    static RPSysSceneCreator *sInstance;
};

#endif