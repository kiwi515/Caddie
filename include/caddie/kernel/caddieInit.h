#ifndef CADDIE_KERNEL_INIT_H
#define CADDIE_KERNEL_INIT_H
#include "types_caddie.h"

namespace caddie
{
    #ifdef __cplusplus
    extern "C"
    {
    #endif

        typedef void(* StaticCtor)(void);
        extern StaticCtor __ctor_loc;
        extern StaticCtor __ctor_end;

        void CaddieMain();
        void InitCpp();

    #ifdef __cplusplus
    }
    #endif
}

#endif