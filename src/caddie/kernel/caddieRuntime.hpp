#ifndef CADDIE_KERNEL_RUNTIME_H
#define CADDIE_KERNEL_RUNTIME_H
#include "caddieAlgorithm.hpp"
#include "types_caddie.hpp"

namespace caddie {

#ifdef __cplusplus
extern "C" {
#endif

extern void* _f_init;
extern void* _e_init;

extern void* _f_text;
extern void* _e_text;

extern void* _f_ctors;
extern void* _e_ctors;

extern void* _f_dtors;
extern void* _e_dtors;

extern void* _f_rodata;
extern void* _e_rodata;

extern void* _f_data;
extern void* _e_data;

#ifdef __cplusplus
}
#endif

// .init section layout
inline const void* GetInitStart() { return &_f_init; }
inline const void* GetInitEnd() { return &_e_init; }
inline u32 GetInitSize() { return PtrDistance(GetInitStart(), GetInitEnd()); }

// .text section layout
inline const void* GetTextStart() { return &_f_text; }
inline const void* GetTextEnd() { return &_e_text; }
inline u32 GetTextSize() { return PtrDistance(GetTextStart(), GetTextEnd()); }

// .ctors section layout
inline const void* GetCtorsStart() { return &_f_ctors; }
inline const void* GetCtorsEnd() { return &_e_ctors; }
inline u32 GetCtorsSize() {
    return PtrDistance(GetCtorsStart(), GetCtorsEnd());
}

// .dtors section layout
inline const void* GetDtorsStart() { return &_f_dtors; }
inline const void* GetDtorsEnd() { return &_e_dtors; }
inline u32 GetDtorsSize() {
    return PtrDistance(GetDtorsStart(), GetDtorsEnd());
}

// .rodata section layout
inline const void* GetRodataStart() { return &_f_rodata; }
inline const void* GetRodataEnd() { return &_e_rodata; }
inline u32 GetRodataSize() {
    return PtrDistance(GetRodataStart(), GetRodataEnd());
}

// .data section layout
inline const void* GetDataStart() { return &_f_data; }
inline const void* GetDataEnd() { return &_e_data; }
inline u32 GetDataSize() { return PtrDistance(GetDataStart(), GetDataEnd()); }

//! @brief Begin ASM block
#define CADDIE_ASM_BEGIN asm volatile {
//! @brief End ASM block
#define CADDIE_ASM_END }

//! @brief Copy GPR to variable
#define CADDIE_ASM_GET_GPR(r, var)                                             \
    asm volatile { mr var, r; }
//! @brief Copy variable to GPR
#define CADDIE_ASM_SET_GPR(r, var)                                             \
    asm volatile { mr r, var; }

//! @brief Backup GPRs to stack frame
#define CADDIE_ASM_SAVE_GPRS                                                   \
    asm volatile {                                                             \
        stwu r1, -0x90(r1);                                                    \
        stmw r3, 0xC(r1);                                                      \
        mflr r12;                                                              \
        stw r12, 0x8(r1);                                                      \
    }

//! @brief Restore GPRs from stack frame
#define CADDIE_ASM_REST_GPRS                                                   \
    asm volatile {                                                             \
        lwz r12, 0x8(r1);                                                      \
        mtlr r12;                                                              \
        lmw r3, 0xC(r1);                                                       \
        addi r1, r1, 0x90;                                                     \
    }

} // namespace caddie

#endif
