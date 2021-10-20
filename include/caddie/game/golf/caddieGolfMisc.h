#ifndef CADDIE_GAME_GOLF_MISC_H
#define CADDIE_GAME_GOLF_MISC_H
#include "types_caddie.h"
#include "types_sp2.h"

namespace caddie
{
    bool CanPlayNextHole(const Sp2::Glf::GlfMain *);
    void RepeatHoleIL();
    void DisablePause();
    bool HasDoneABCheck();
    void SetPinPos();
}

#endif