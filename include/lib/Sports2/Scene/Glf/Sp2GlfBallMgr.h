#ifndef SP2_GLF_GLFBALL_MGR
#define SP2_GLF_GLFBALL_MGR
#include "Sp2GlfBall.h"
#include "Sp2GlfDefine.h"
#include "caddieAssert.h"
#include "types_sp2.h"

namespace Sp2 {
namespace Glf {

class GlfBallMgr {
  public:
    static GlfBall& GetBall(int i) {
        CADDIE_ASSERT(i < PLAYER_MAX);
        CADDIE_ASSERT(sGlfBalls[i] != NULL);
        return *sGlfBalls[i];
    }

  private:
    static GlfBall* sGlfBalls[PLAYER_MAX];
};

} // namespace Glf
} // namespace Sp2

#endif
