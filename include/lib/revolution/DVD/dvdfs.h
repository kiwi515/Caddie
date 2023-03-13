#ifndef RVL_SDK_DVD_DVDFS_H
#define RVL_SDK_DVD_DVDFS_H
#include <revolution/DVD/dvd.h>
#include <revolution/OS.h>
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

extern BOOL __DVDLongFileNameFlag;
extern OSThreadQueue __DVDThreadQueue;

void __DVDFSInit(void);
s32 DVDConvertPathToEntrynum(const char* path);
BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* info);
BOOL DVDOpen(const char* path, DVDFileInfo* info);
BOOL DVDClose(DVDFileInfo* info);
BOOL DVDGetCurrentDir(char* string, u32 maxlen);
BOOL DVDReadAsyncPrio(DVDFileInfo* info, void* dst, u32 size, s32 offset,
                      DVDFileCallback callback, u32 prio);
s32 DVDReadPrio(DVDFileInfo* info, void* dst, u32 size, s32 offset, u32 prio);

#ifdef __cplusplus
}
#endif
#endif
