#ifndef MSL_STDIO_H
#define MSL_STDIO_H
#include <types.h>
#include <STL/stdarg.h>
#ifdef __cplusplus
extern "C" {
#endif

int snprintf(char *, size_t, const char *, ...);
int sprintf(char *, const char *, ...);
int vsnprintf(char *, size_t, const char *, va_list);
int vsprintf(char *, const char *, va_list);
int vprintf(const char *, va_list);

#ifdef __cplusplus
}
#endif
#endif
