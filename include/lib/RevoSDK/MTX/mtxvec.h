#ifndef RVL_SDK_MTX_MTXVEC_H
#define RVL_SDK_MTX_MTXVEC_H
#include <MTX/mtx.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void PSMTXMultVec(const Mtx, const Vec*, Vec*);

#ifdef __cplusplus
}
#endif
#endif
