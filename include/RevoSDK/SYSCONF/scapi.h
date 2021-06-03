#ifndef REVOSDK_SC_API_H
#define REVOSDK_SC_API_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

u32 SCGetLanguage();

enum SCLang_t
{
    LANG_JAPANESE = 0,
    LANG_ENGLISH = 1,
    LANG_GERMAN = 2,
    LANG_FRENCH = 3,
    LANG_SPANISH = 4,
    LANG_ITALIAN = 5,
    LANG_DUTCH = 6,
    LANG_CHINESE_S = 7,
    LANG_CHINESE_T = 8,
    LANG_KOREAN = 9
};

#ifdef __cplusplus
}
#endif
#endif