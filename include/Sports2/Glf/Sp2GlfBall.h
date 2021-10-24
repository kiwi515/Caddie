#ifndef SP2_GLF_GLFBALL_H
#define SP2_GLF_GLFBALL_H
#include "types_sp2.h"

namespace Sp2
{
    namespace Glf
    {
        // sizeof = 0x1E0
        class GlfBall
        {
        public:
            virtual ~GlfBall();

            u32 GetLifetime() const { return mLifetime; }
            void SetLifetime(u32 time) { mLifetime = time; }
        private:
            char UNK_0x4[0x54 - 0x4];
            u32 mLifetime;
        };
    }
}

#endif