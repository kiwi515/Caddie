#ifndef SP2_OBJ_806F4CD0_H
#define SP2_OBJ_806F4CD0_H
#include "types_sp2.h"

namespace caddie
{
    class Obj806f4cd0
    {
    public:
        inline static Obj806f4cd0 * GetInstance() { return sInstance; }
        
        UNKTYPE func_802352d4();

    private:
        static Obj806f4cd0 *sInstance;
    };
}

#endif