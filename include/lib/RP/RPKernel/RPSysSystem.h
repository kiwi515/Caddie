#ifndef RP_KERNEL_SYSTEM_H
#define RP_KERNEL_SYSTEM_H
#include "types_caddie.hpp"

class RPSysSystem {
public:
    static RPSysSystem& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    EGG::Heap* getSystemHeap() const { return mSystemHeap; }
    EGG::Heap* getSceneHeap() const { return mRootSceneHeap; }

private:
    RPSysSystem();
    virtual ~RPSysSystem();

private:
    // System heap (2MB, MEM2)
    EGG::Heap* mSystemHeap; // at 0x4
    // Resource heap (23.5MB, MEM2)
    EGG::Heap* mResourceHeap; // at 0x8
    // Resource cache heap (4MB, MEM2)
    EGG::Heap* mResCacheHeap; // at 0xC

    // Root scene heap (5.5MB, MEM1)
    EGG::Heap* mRootSceneHeap; // at 0x10
    // Root scene "DependOnTarget" heap (4MB, MEM1)
    EGG::Heap* mRootSceneDependHeap; // at 0x14

    // Debug(?) heap (256B, MEM2, Locked)
    EGG::Heap* mDebugHeap; // at 0x18

    static RPSysSystem* sInstance;
};

#endif
