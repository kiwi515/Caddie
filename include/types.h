#ifndef TYPES_H
#define TYPES_H
#include <kamek.h>
#include <macros.h>
#include <stddef.h>

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;

typedef int UNKWORD;
typedef void UNKTYPE;

typedef enum { FALSE, TRUE } BOOL;

#define ARRAY_COUNT(x) (sizeof((x)) / sizeof(((x)[0])))

/**
 * @brief Define a localizable message.
 * @note Evaluated at compile time
 */
#ifdef CADDIE_REGION_NTSC_U
#define CADDIE_LOCALIZE(NTSC_U, PAL, NTSC_J, KOR) NTSC_U
#elif CADDIE_REGION_PAL
#define CADDIE_LOCALIZE(NTSC_U, PAL, NTSC_J, KOR) PAL
#elif CADDIE_REGION_NTSC_J
#define CADDIE_LOCALIZE(NTSC_U, PAL, NTSC_J, KOR) NTSC_J
#elif CADDIE_REGION_KOR
#define CADDIE_LOCALIZE(NTSC_U, PAL, NTSC_J, KOR) KOR
#else
#error "No language defined!"
#endif

#define CADDIE_ENUM_MAX(enum) (ARRAY_COUNT((enum)) - 1)

#endif
