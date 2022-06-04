#ifndef SP2_GLF_GLFBALLMGR
#define SP2_GLF_GLFBALLMGR
#include "types_sp2.h"
#include "Sp2GlfBall.h"
#include "Sp2GlfDefine.h"

#include "caddieAssert.h"

namespace Sp2
{
    namespace Glf
    {
        class GlfBallMgr
        {
        public:
            static GlfBall * GetBall(int i)
            {
                CADDIE_ASSERT(i < PLAYER_MAX);
                return sGlfBalls[i];
            }
        private:
            static GlfBall *sGlfBalls[PLAYER_MAX];
        };
    }
}

#endif
