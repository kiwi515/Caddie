#ifndef RVL_SDK_DVD_H
#define RVL_SDK_DVD_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct DVDFileInfo;

typedef void (*DVDAsyncCallback)(s32 result, struct DVDFileInfo* info);

typedef struct DVDCommandBlock {
    char _00[0x30];
} DVDCommandBlock;

typedef struct DVDFileInfo {
    DVDCommandBlock block;     // at 0x0
    u32 offset;                // at 0x30
    u32 size;                  // at 0x34
    DVDAsyncCallback callback; // at 0x38
} DVDFileInfo;

#ifdef __cplusplus
}
#endif
#endif
