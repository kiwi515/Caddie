#ifndef SP2_GLF_GLFMAIN_H
#define SP2_GLF_GLFMAIN_H
#include "types_caddie.h"

#include <Scene/Glf/Sp2GlfDefine.h>

namespace Sp2 {
namespace Glf {

class GlfMain {
public:
    static GlfMain& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    void setPause(bool pause) { mIsPause = pause; }

private:
    GlfMain();
    virtual ~GlfMain();

    char _04[0x18 - 0x4]; // at 0x4
    bool mIsPause;        // at 0x18

    static GlfMain* sInstance;
};

} // namespace Glf
} // namespace Sp2

#endif
