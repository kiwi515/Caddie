#ifndef EGG_UTIL_EXCEPTION_H
#define EGG_UTIL_EXCEPTION_H
#include "types_egg.h"

#include <revolution/KPAD.h>

namespace EGG {

class Exception {
public:
    typedef void (*CallBackFunc)(KPADStatus* status);

    static Exception* create(u16, u16, u16, Heap*, u16);
    static void setUserCallback(const u16*);

    static CallBackFunc UserCallBackFunc;
};

} // namespace EGG

#endif
