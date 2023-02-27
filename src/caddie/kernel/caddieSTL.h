#ifndef CADDIE_KERNEL_STL_H
#define CADDIE_KERNEL_STL_H
#include "types_caddie.h"

#include <cstdio>
#include <cstring>

namespace cstl {

bool isdigit(char c);
bool isalpha(char c);
bool isupper(char c);
bool islower(char c);

char* strchr(const char* str, char c);
s32 strtol(const char* str, char** endptr, int base);
u32 strtoul(const char* str, char** endptr, int base);

} // namespace cstl

#endif
