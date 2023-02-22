#ifndef EGG_CORE_DECOMP_H
#define EGG_CORE_DECOMP_H
#include "types_egg.h"

namespace EGG {

class Decomp {
public:
    static int decode(u8*, u8*);
    static int decodeSZS(u8*, u8*);
    static int decodeASH(u8*, u8*);
    static int decodeASR(u8*, u8*);
    static int checkCompressed(u8*);
    static int getExpandSize(u8*);
};

} // namespace EGG

#endif
