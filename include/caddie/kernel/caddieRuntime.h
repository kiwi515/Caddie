#ifndef CADDIE_KERNEL_RUNTIME_H
#define CADDIE_KERNEL_RUNTIME_H
#include "types_caddie.h"

namespace caddie {

#ifdef __cplusplus
extern "C" {
#endif

//! @brief C++ static initializer function pointer
typedef void (*StaticCtor)(void);
//! @brief Static constructor list begin ptr
extern StaticCtor __ctor_loc;
//! @brief Static constructor list end ptr
extern StaticCtor __ctor_end;

#ifdef __cplusplus
}
#endif

//! @brief Begin ASM block
#define CADDIE_ASM_BEGIN asm volatile {
//! @brief End ASM block
#define CADDIE_ASM_END }

//! @brief Copy GPR to variable
#define CADDIE_GET_GPR(r, var)                                                 \
    asm volatile { mr var, r; }
//! @brief Copy variable to GPR
#define CADDIE_SET_GPR(r, var)                                                 \
    asm volatile { mr r, var; }

//! @brief Backup GPRs to stack frame
#define CADDIE_SAVE_GPRS                                                       \
    asm volatile {                                                             \
        stwu r1, -0x90(r1);                                                    \
        stmw r3, 0xC(r1);                                                      \
        mflr r12;                                                              \
        stw r12, 0x8(r1);                                                      \
    }

//! @brief Restore GPRs from stack frame
#define CADDIE_REST_GPRS                                                       \
    asm volatile {                                                             \
        lwz r12, 0x8(r1);                                                      \
        mtlr r12;                                                              \
        lmw r3, 0xC(r1);                                                       \
        addi r1, r1, 0x90;                                                     \
    }

} // namespace caddie

#endif
