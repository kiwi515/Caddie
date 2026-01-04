#ifndef SP2_GLF_SEQUENCE_MGR_H
#define SP2_GLF_SEQUENCE_MGR_H
#include "types_caddie.h"

#include <Scene/Glf/Sp2GlfDefine.h>

namespace Sp2 {
namespace Glf {

class Phase {
public:
    void Enter();
};

class SequenceMain {
public:
    void NextShot();

public:
    class Phase_CupIn : public Phase {
        char _00[0x14];
    };

    class Phase_BallStop : public Phase {
        char _00[0x14];
    };

public:
    char _00[0x7C];
    Phase_CupIn CupIn; // at 0x7C
    char _90[0xA4 - 0x90];
    Phase_BallStop BallStop; // at 0x90
};

class SequenceMgr {
public:
    static SequenceMgr& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    void Calculate();

    SequenceMain* GetSequenceMain() const { return mpSequenceMain; }

private:
    virtual ~SequenceMgr();

private:
    SequenceMain* mpSequenceMain; // at 0x4

    static SequenceMgr* sInstance;
};

} // namespace Glf
} // namespace Sp2

#endif
