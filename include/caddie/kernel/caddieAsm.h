#ifndef CADDIE_KERNEL_ASM_H
#define CADDIE_KERNEL_ASM_H

#define CADDIE_ASM_BEGIN asm volatile {
#define CADDIE_ASM_END }

#define CADDIE_GET_GPR(r, var) asm volatile { mr var, r; }
#define CADDIE_SET_GPR(r, var) asm volatile { mr r, var; }

#define CADDIE_SAVE_GPRS \
    asm volatile { \
        stwu r1, -0x90(r1); \
        stmw r3, 0xC(r1); \
        mflr r12; \
        stw r12, 0x8(r1); \
    } \

#define CADDIE_REST_GPRS \
    asm volatile { \
        lwz r12, 0x8(r1); \
        mtlr r12; \
        lmw r3, 0xC(r1); \
        addi r1, r1, 0x90; \
    } \

#endif
