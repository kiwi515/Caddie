#ifndef REVOSDK_OS_FATAL_H
#define REVOSDK_OS_FATAL_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

void OSFatal(const u32 *fg, const u32 *bg, const char *message);

#ifdef __cplusplus
}
#endif
#endif