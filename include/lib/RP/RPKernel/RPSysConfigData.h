#ifndef RP_KERNEL_CONFIG_DATA_H
#define RP_KERNEL_CONFIG_DATA_H
#include "types_rp.h"

#include <egg/core/eggSystem.h>

/**
 * @brief Engine configuration data
 * @details Hooks RP engine into EGG's system
 */
class RPSysConfigData : public EGG::ConfigurationData {
public:
    static EGG::Heap* getRootHeapMem1() { return sConfigData.mRootHeapMem1; }
    static EGG::Heap* getRootHeapMem2() { return sConfigData.mRootHeapMem2; }
    static EGG::Heap* getSystemHeap() { return sConfigData.mSystemHeap; }

private:
    static RPSysConfigData sConfigData;
};

#endif
