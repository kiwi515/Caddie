#ifndef CADDIE_SCENE_GLF_UTIL_H
#define CADDIE_SCENE_GLF_UTIL_H
#include "types_caddie.h"
#include <Sports2/Scene/Glf/Sp2GlfDefine.h>

namespace caddie
{
    class GlfUtil
    {
    public:
        static bool IsCurrentFirstHole();
        static bool IsFirstHoleInternal(Sp2::Glf::GameMode gm, u32 hole);
        static bool IsFirstHole(Sp2::Glf::GameMode gm, u32 hole);

        static bool IsCurrentRoundOver();
        static bool IsNextRoundOver();
        static bool IsRoundOverInternal(Sp2::Glf::GameMode gm, u32 hole);
        static bool IsRoundOver(Sp2::Glf::GameMode gm, u32 hole);
    };
}

#endif