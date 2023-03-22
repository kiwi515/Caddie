#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include "caddieAssert.h"
#include "types_nw4r.h"
#include "types_rp.h"

#include <egg/core.h>

class RPSysSceneMgr : public EGG::SceneManager {
public:
    static RPSysSceneMgr& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    bool isNormalState() const;

private:
    virtual ~RPSysSceneMgr();

private:
    static RPSysSceneMgr* sInstance;
};

#endif
