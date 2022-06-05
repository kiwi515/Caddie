#ifndef REVOSDK_OS_CONTEXT_H
#define REVOSDK_OS_CONTEXT_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 gprs[32]; // at 0x0
    u32 cr;       // at 0x80
    u32 lr;       // at 0x84
    u32 ctr;      // at 0x88
    u32 xer;      // at 0x8C
    f64 fprs[32]; // at 0x90
    char UNK_0x190[0x8];
    u32 srr0; // at 0x198
    u32 srr1; // at 0x19C
    // . . .
} OSContext;

#ifdef __cplusplus
}
#endif
#endif
