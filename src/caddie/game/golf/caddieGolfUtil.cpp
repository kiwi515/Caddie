#include "caddieGolfUtil.h"

namespace caddie
{
    u32 GetHoleMaxPin(u32 hole)
    {
        switch(hole)
        {
            // Hole 1 has 3 pins
            case 0: return 3;
            // Hole 18 has 1 pin
            case 17: return 1;
            // All other holes have 6 pins
            default: return 6;
        }
    }
}