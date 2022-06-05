#ifndef EGG_UTIL_EXCEPTION_H
#define EGG_UTIL_EXCEPTION_H
#include "types_egg.h"

namespace EGG {

class Exception {
  public:
    static Exception* create(u16, u16, u16, Heap*, u16);
    static void setUserCallback(const u16*);
};

} // namespace EGG

#endif
