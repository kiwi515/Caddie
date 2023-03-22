#ifndef EGG_CORE_SCENE_H
#define EGG_CORE_SCENE_H
#include "types_egg.h"

#include <egg/core/eggDisposer.h>

namespace EGG {

class Scene : public EGG::Disposer {
public:
    Scene();

    virtual ~Scene();
    inline virtual void calc() {}
    inline virtual void draw() {}
    inline virtual void enter() {}
    inline virtual void exit() {}
    inline virtual void reinit() {}
    inline virtual void incoming_childDestroy() {}
    inline virtual void outgoing_childCreate() {}

    inline Heap* getHeap() const { return mCreatorHeap; }
    inline Heap* getHeap_Mem1() const { return mHeap_Mem1; }
    inline Heap* getHeap_Mem2() const { return mHeap_Mem2; }
    inline Heap* getHeap_Debug() const { return mHeap_Debug; }
    inline Scene* getParentScene() const { return mParentScene; }
    inline Scene* getChildScene() const { return mChildScene; }
    inline s32 getSceneID() const { return mSceneID; }

private:
    Heap* mCreatorHeap;      // at 0x10
    Heap* mHeap_Mem1;        // at 0x14
    Heap* mHeap_Mem2;        // at 0x18
    Heap* mHeap_Debug;       // at 0x1C
    Scene* mParentScene;     // at 0x20
    Scene* mChildScene;      // at 0x24
    s32 mSceneID;            // at 0x28
    SceneManager* mSceneMgr; // at 0x2C
};

} // namespace EGG

#endif
