#ifndef SP2_GLF_GLFMAIN_H
#define SP2_GLF_GLFMAIN_H
#include "caddieAssert.h"
#include "types_sp2.h"

#include <Scene/Glf/Sp2GlfDefine.h>

namespace Sp2 {
namespace Glf {

class GlfMain {
  public:
    static GlfMain& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    GameMode getGamemode() const { return (GameMode)mGamemode; }
    void setGamemode(GameMode gm) { mGamemode = gm; }

    u32 getCurrentHole() const { return mCurrentHole; }
    void setCurrentHole(u32 i) { mCurrentHole = i; }

    u32 getPin() const { return mPin; }
    void setPin(u32 i) { mPin = i; }

  private:
    GlfMain();
    virtual ~GlfMain();

    u32 mGamemode; // at 0x4
    UNKWORD WORD_0x8;
    u32 mCurrentHole; // at 0xC
    char UNK_0x10[0x38 - 0x10];
    u32 mPin; // at 0x38
    char UNK_0x3C[0x1D70 - 0x3C];

    static GlfMain* sInstance;
};

} // namespace Glf
} // namespace Sp2

#endif
