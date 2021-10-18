#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include "types_rp.h"
#include "types_nw4r.h"

#include "caddieAssert.h"

#include "eggSceneManager.h"

class RPSysSceneMgr : public EGG::SceneManager
{
public:
    inline static RPSysSceneMgr * getInstance()
    {
        return sInstance;
    }

private:
    virtual ~RPSysSceneMgr();
    static RPSysSceneMgr *sInstance;
};

#endif