#ifndef SP2_STATIC_MEM_H
#define SP2_STATIC_MEM_H
#include "types_caddie.hpp"

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

private:
    char _00[0x18];
    u32 mSequence;

    static StaticMem* sInstance;
};

} // namespace Sp2

#endif
