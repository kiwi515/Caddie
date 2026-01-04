#ifndef RP_SPORTS_GLF_CLUB_MANAGER_H
#define RP_SPORTS_GLF_CLUB_MANAGER_H
#include "types_RP.h"
#include "types_caddie.h"

#include <nw4r/math/math_types.h>

class RPGlfClub;

class RPGlfClubManager {
public:
    static RPGlfClubManager& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    RPGlfClub* GetActiveClub() const {
        CADDIE_ASSERT(mClubNo < 8);
        return mpClubs[mClubNo];
    }

private:
    char _00[0xC];
    RPGlfClub* mpClubs[8]; // at 0xC
    u32 mClubNo;           // at 0x2C

    static RPGlfClubManager* sInstance;
};

#endif
