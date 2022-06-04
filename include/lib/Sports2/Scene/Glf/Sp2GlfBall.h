#ifndef SP2_GLF_GLFBALL_H
#define SP2_GLF_GLFBALL_H
#include "types_sp2.h"

namespace Sp2 {
namespace Glf {

class GlfBall {
  public:
    virtual ~GlfBall();

    u32 GetLifetime() const { return mLifetime; }
    void SetLifetime(u32 time) { mLifetime = time; }

    void Stop(bool);

  private:
    char UNK_0x4[0x54 - 0x4];
    u32 mLifetime; // at 0x54
};

} // namespace Glf
} // namespace Sp2

#endif
