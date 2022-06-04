#ifndef MSL_STDIO_H
#define MSL_STDIO_H
#include <STL/stdarg.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int snprintf(char*, size_t, const char*, ...);
int sprintf(char*, const char*, ...);
int vsnprintf(char*, size_t, const char*, va_list);
int vsprintf(char*, const char*, va_list);
int vprintf(const char*, va_list);

#ifdef __cplusplus
}
#endif
#endif
