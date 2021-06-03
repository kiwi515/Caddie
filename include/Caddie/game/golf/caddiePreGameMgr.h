#ifndef CADDIE_GOLF_PRE_GAME_MGR_H
#define CADDIE_GOLF_PRE_GAME_MGR_H
#include <types.h>
#include <Glf/Sp2GlfDefine.h>

namespace caddie
{
    class PreGameManager
    {
    public:
        static void setBlindFlag();
        static u32 getGameStartHole(Glf::CourseSelBtn lytBtn);

    private:
        static u32 getGameStartHoleFromBtn(Glf::CourseSelBtn lytBtn);
    };
}

#endif