#ifndef SP2_STATIC_MEM_H
#define SP2_STATIC_MEM_H
#include "types_sp2.h"

#include "caddieAssert.h"

namespace Sp2
{
    class StaticMem
    {
    public:
        inline static StaticMem *getInstance()
        { 
            return sInstance;
        }

        int getStaticVar(int var, bool b);
        void setStaticVar(int var, int value, bool b);

    private:
        static StaticMem *sInstance;
    };
}

#endif