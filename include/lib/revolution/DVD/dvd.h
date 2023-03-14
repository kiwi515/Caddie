#ifndef RVL_SDK_DVD_H
#define RVL_SDK_DVD_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct DVDCommandBlock;
typedef struct DVDDiskID;
typedef struct DVDDriveBlock;
typedef struct DVDFileInfo;
typedef struct OSAlarm;

typedef void (*DVDCommandCallback)(s32 result, struct DVDCommandBlock* block);
typedef void (*DVDFileCallback)(s32 result, struct DVDFileInfo* info);
typedef void (*DVDInquiryCallback)(s32, struct DVDDriveBlock*);

typedef struct DVDCommandBlock {
    struct DVDCommandBlock* next; // at 0x0
    struct DVDCommandBlock* prev; // at 0x4
    u32 command;                  // at 0x8
    s32 state;                    // at 0xC
    u32 offset;                   // at 0x10
    u32 length;                   // at 0x14
    void* addr;                   // at 0x18
    u32 transferSize;             // at 0x1C
    u32 transferProgress;         // at 0x20
    struct DVDDiskID* id;         // at 0x24
    DVDCommandCallback callback;  // at 0x28
    void* userData;               // at 0x2C
} DVDCommandBlock;

typedef struct DVDFileInfo {
    DVDCommandBlock cb;       // at 0x0
    void* addr;               // at 0x30
    u32 length;               // at 0x34
    DVDFileCallback callback; // at 0x38
} DVDFileInfo;

typedef struct DVDDriveBlock {
    char UNK_0x0[0xC];
    UNKWORD WORD_0xC;
    char UNK_0x10[0x30 - 0x10];
} DVDDriveBlock;

typedef struct DVDDriveInfo {
    u16 revision;    // at 0x0
    u16 deviceCode;  // at 0x2
    u32 releaseDate; // at 0x4
    char padding[32 - 0x8];
} DVDDriveInfo;

extern u32 __DVDLayoutFormat;

void DVDInit(void);

BOOL DVDInquiryAsync(DVDDriveBlock*, DVDDriveInfo*, DVDInquiryCallback);

u32 __DVDGetCoverStatus(void);

void __DVDPrepareReset(void);
BOOL __DVDTestAlarm(struct OSAlarm*);

#ifdef __cplusplus
}
#endif
#endif
