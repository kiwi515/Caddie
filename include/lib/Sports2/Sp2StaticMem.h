#ifndef SP2_STATIC_MEM_H
#define SP2_STATIC_MEM_H
#include "types_caddie.hpp"

#include <RP/RPSystem/RPSysScene.h>
namespace Sp2 {

class StaticMem {
public:
    static StaticMem& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    int getStaticVar(int var, bool b);
    void setStaticVar(int var, int value, bool b);

    u32 getSceneSeq() const { return mSequence; }

    RPSysScene::IslandType getIslandType() const { return mIslandType; }
    void setIslandType(RPSysScene::IslandType type) { mIslandType = type; }

private:
    char _00[0x18];
    u32 mSequence; // at 0x18
    char _1C[0x380 - 0x1C];
    RPSysScene::IslandType mIslandType; // at 0x380

    static StaticMem* sInstance;
};

} // namespace Sp2

#endif
