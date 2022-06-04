#ifndef CADDIE_KERNEL_RUNTIME_H
#define CADDIE_KERNEL_RUNTIME_H
#include "types_caddie.h"

namespace caddie {

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*StaticCtor)(void);
extern StaticCtor __ctor_loc;
extern StaticCtor __ctor_end;

#ifdef __cplusplus
}
#endif

#define CADDIE_ASM_BEGIN asm volatile {
#define CADDIE_ASM_END }

#define CADDIE_GET_GPR(r, var)                                                 \
    asm volatile { mr var, r; }
#define CADDIE_SET_GPR(r, var)                                                 \
    asm volatile { mr r, var; }

#define CADDIE_SAVE_GPRS                                                       \
    asm volatile {                                                             \
        stwu r1, -0x90(r1);                                                    \
        stmw r3, 0xC(r1);                                                      \
        mflr r12;                                                              \
        stw r12, 0x8(r1);                                                      \
    }

#define CADDIE_REST_GPRS                                                       \
    asm volatile {                                                             \
        lwz r12, 0x8(r1);                                                      \
        mtlr r12;                                                              \
        lmw r3, 0xC(r1);                                                       \
        addi r1, r1, 0x90;                                                     \
    }

} // namespace caddie

#endif
