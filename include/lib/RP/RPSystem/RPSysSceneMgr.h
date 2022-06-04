#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include "caddieAssert.h"
#include "types_nw4r.h"
#include "types_rp.h"

#include <egg/core/eggSceneManager.h>

class RPSysSceneMgr : public EGG::SceneManager {
  public:
    static RPSysSceneMgr& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

  private:
    virtual ~RPSysSceneMgr();

  private:
    static RPSysSceneMgr* sInstance;
};

#endif
