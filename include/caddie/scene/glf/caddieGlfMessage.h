#ifndef CADDIE_SCENE_GLF_MESSAGE_H
#define CADDIE_SCENE_GLF_MESSAGE_H
#include "types_caddie.h"

#include <Sports2/Scene/Glf/Sp2GlfDefine.h>

namespace caddie
{
    extern const char* MSG_MENU_TITLE;
    extern const char* MSG_HOLE;
    extern const char* MSG_REPEAT_HOLE;
    extern const char* MSG_PIN_TYPE;
    extern const char* MSG_WIND_DIR;
    extern const char* MSG_WIND_SPD;
    extern const char* MSG_WIND_SPD_RANGE;
    extern const char* MSG_APPLY;
    extern const char* MSG_QUIT;

    enum EPin
    {
        PIN_1,
        PIN_2,
        PIN_3,
        PIN_4,
        PIN_5,
        PIN_6,
        PIN_SCORE,
        PIN_RND_ALL,
        PIN_RND_A,
        PIN_RND_B,

        PIN_MAX
    };
    extern const char* ENUM_PIN_TYPE[PIN_MAX];

    enum EHole1Pin
    {
        H1_PIN_1,
        H1_PIN_2,
        H1_PIN_3,
        H1_PIN_RND_ALL,

        H1_PIN_MAX
    };
    extern const char* ENUM_PIN_TYPE_HOLE1[H1_PIN_MAX];

    enum ESpecialPin
    {
        SP_PIN_1,
        SP_PIN_2,
        SP_PIN_3,
        SP_PIN_4,
        SP_PIN_5,
        SP_PIN_6,
        SP_PIN_RND_ALL,

        SP_PIN_MAX
    };
    extern const char* ENUM_PIN_TYPE_SPECIAL[SP_PIN_MAX];
    
    enum EWindDir
    {
        DIR_S,
        DIR_SE,
        DIR_E,
        DIR_NE,
        DIR_N,
        DIR_NW,
        DIR_W,
        DIR_SW,
        DIR_RND,

        DIR_MAX
    };
    extern const char* ENUM_WIND_DIR[DIR_MAX];

    const int WIND_SPD_RANDOM = Sp2::Glf::WIND_MAX + 1;
    extern const char* ENUM_WIND_SPD[];

    enum EWindSpdRange
    {
        RANGE_0_10,
        RANGE_0_5,
        RANGE_5_10,
        RANGE_10_15,
        RANGE_0_15,

        RANGE_MAX
    };
    extern const char* ENUM_WIND_SPD_RANGE[RANGE_MAX];
}

#endif