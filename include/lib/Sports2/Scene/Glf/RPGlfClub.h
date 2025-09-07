#ifndef RP_SPORTS_GLF_CLUB_H
#define RP_SPORTS_GLF_CLUB_H
#include "types_RP.h"
#include "types_caddie.h"

#include <nw4r/math/math_types.h>

class RPGlfClub {
public:
    enum EType {
        EType_WD,
        EType_IR,
        EType_SW,
        EType_PT,
    };

    EType GetType() const { return mType; }

private:
    char _00[0x4];
    EType mType; // at 0x4
};

#endif
