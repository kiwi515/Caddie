#ifndef SP2_STATIC_MEM_H
#define SP2_STATIC_MEM_H
#include "caddieAssert.h"
#include "types_sp2.h"

namespace Sp2 {

class StaticMem {
  public:
    static StaticMem& getInstance() {
        CADDIE_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    int getStaticVar(int var, bool b);
    void setStaticVar(int var, int value, bool b);

  private:
    static StaticMem* sInstance;
};

} // namespace Sp2

#endif
