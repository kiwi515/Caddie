#ifndef RP_SPORTS_GLF_SIM_MANAGER_H
#define RP_SPORTS_GLF_SIM_MANAGER_H
#include "caddieAssert.h"
#include "types_Sp2.h"

#include <Scene/Glf/Sp2GlfDefine.h>

class RPGlfBall;

class RPGlfSimManager {
public:
    static RPGlfBall* GetSimBall() { return spSimBall; }

public:
    static RPGlfBall* spSimBall;
};

#endif
