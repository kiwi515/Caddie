#ifndef REVOSDK_SC_API_H
#define REVOSDK_SC_API_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

u32 SCGetLanguage();

typedef enum
{
    SC_JAPANESE = 0,
    SC_ENGLISH = 1,
    SC_GERMAN = 2,
    SC_FRENCH = 3,
    SC_SPANISH = 4,
    SC_ITALIAN = 5,
    SC_DUTCH = 6,
    SC_CHINESE_S = 7,
    SC_CHINESE_T = 8,
    SC_KOREAN = 9
} SCLang;

#ifdef __cplusplus
}
#endif
#endif
