#ifndef REVOSDK_OS_ERROR_H
#define REVOSDK_OS_ERROR_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

void OSReport(const char *, ...);
void OSPanic(const char *, int, const char *, ...);

#ifdef __cplusplus
}
#endif
#endif
