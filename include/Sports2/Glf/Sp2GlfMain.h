#ifndef SP2_GLF_MAIN_H
#define SP2_GLF_MAIN_H
#include "types_sp2.h"

#include "caddieAssert.h"

namespace Sp2
{
    namespace Glf
    {
        class GlfMain
        {
        public:
            inline static GlfMain *getInstance()
            {
                return sInstance;
            }

            u32 getGamemode() const { return mGamemode; }
            void setGamemode(u32 gm) { mGamemode = gm; }

            u32 getCurrentHole() const { return mCurrentHole; }
            void setCurrentHole(u32 i) { mCurrentHole = i; }

            u32 getPin() const { return mPin; }
            void setPin(u32 i) { mPin = i; }

        private:
            GlfMain();
            virtual ~GlfMain();

            u32 mGamemode; // at 0x4
            UNKWORD WORD_0x8;
            u32 mCurrentHole; // at 0xC
            char UNK_0xC[0x38 - 0xC];
            u32 mPin;
            char UNK_0x10[0x1D70];

            static GlfMain *sInstance;
        };
    }
}

#endif