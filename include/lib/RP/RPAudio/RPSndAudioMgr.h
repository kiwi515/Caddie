#ifndef RP_AUDIO_SND_AUDIO_MGR_H
#define RP_AUDIO_SND_AUDIO_MGR_H
#include "types_RP.h"
#include "types_caddie.hpp"

struct BaseA {
    char _00[0x10C];
};

struct BaseB {
    virtual UNKTYPE VF_0x8() = 0;
    virtual UNKTYPE VF_0xC() = 0;
    virtual UNKTYPE VF_0x10() = 0;
    virtual UNKTYPE VF_0x14() = 0;
    virtual UNKTYPE VF_0x18() = 0;
    virtual UNKTYPE VF_0x1C() = 0;
    virtual UNKTYPE VF_0x20() = 0;
    virtual UNKTYPE VF_0x24() = 0;
    virtual bool loadGroup(u32 grp, u32, u32);
};

class RPSndAudioMgr : public BaseA, public BaseB {
public:
    static RPSndAudioMgr& GetInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    static void startSound(u32 snd);

    static void stopAllSound();

private:
    static RPSndAudioMgr* sInstance;
};

#endif
