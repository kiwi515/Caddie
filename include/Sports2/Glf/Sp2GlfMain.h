#ifndef SP2_GLF_MAIN_H
#define SP2_GLF_MAIN_H
#include "types_sp2.h"

#include "caddieAssert.h"

namespace Glf
{
    class GlfMain
    {
    public:
        inline static GlfMain *getInstance()
        {
            return sInstance;
        }

        inline u32 getGamemode() { return mGamemode; }
        inline void setGamemode(u32 gm) { mGamemode = gm; }

        inline u32 getCurrentHole() { return mCurrentHole; }
        inline void setCurrentHole(u32 i) { mCurrentHole = i; }

    private:
        GlfMain();
        virtual ~GlfMain();

        u32 mGamemode; // at 0x4
        UNKWORD WORD_0x8;
        u32 mCurrentHole; // at 0xC
        char UNK_0x10[0x1D70];

        static GlfMain *sInstance;
    };
}

#endif