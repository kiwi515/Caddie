#ifndef NW4R_LYT_RES_H
#define NW4R_LYT_RES_H
#include <nw4r/math.h>
#include <types_nw4r.h>

namespace nw4r {
namespace lyt {
namespace res {

struct DataBlockHeader {
    char kind[4]; // at 0x0
    u32 size;     // at 0x4
};

struct BinaryFileHeader {
    char kind[4];   // at 0x0
    u16 byteOrder;  // at 0x4
    u16 version;    // at 0x6
    u32 fileSize;   // at 0x8
    u16 headerSize; // at 0xC
    u16 numBlocks;  // at 0xE
};

} // namespace res

struct ResBlockSet {
    /*
    18d11: <50> TAG_member
            AT_sibling(0x18d43)
            AT_name("pTextureList")
            AT_mod_u_d_type(<6>MOD_pointer_to MOD_const 0x18acd)
            AT_public("")
            AT_location(<6>OP_CONST(0x0) OP_ADD )

    18d43: <47> TAG_member
            AT_sibling(0x18d72)
            AT_name("pFontList")
            AT_mod_u_d_type(<6>MOD_pointer_to MOD_const 0x18b8d)
            AT_public("")
            AT_location(<6>OP_CONST(0x4) OP_ADD )

    18d72: <51> TAG_member
            AT_sibling(0x18da5)
            AT_name("pMaterialList")
            AT_mod_u_d_type(<6>MOD_pointer_to MOD_const 0x18c4b)
            AT_public("")
            AT_location(<6>OP_CONST(0x8) OP_ADD )

    18da5: <49> TAG_member
            AT_sibling(0x18dd6)
            AT_name("pResAccessor")
            AT_mod_u_d_type(<5>MOD_pointer_to 0x15d0c)
            AT_public("")
            AT_location(<6>OP_CONST(0xc) OP_ADD )
    18dd6: <4>
    */
};

} // namespace lyt
} // namespace nw4r

#endif
