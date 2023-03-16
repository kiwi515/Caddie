from caddie_py.binary.block.block_base import BlockBase
from caddie_py.binary.types.structure import Structure
from caddie_py.binary.types.primitive import Primitive
from caddie_py.binary.types.gx import *


class AlphaCompare(Structure):
    """Material alpha comparison structure"""
    MEMBERS = [
        GXCompare("u8", "comp"),
        GXAlphaOp("u8", "op"),
        Primitive("u8", "ref0"),
        Primitive("u8", "ref1")
    ]


class ChanCtrl(Structure):
    """Material channel control structure"""
    MEMBERS = [
        GXColorSrc("u8", "color_src"),
        GXColorSrc("u8", "alpha_src"),
        Primitive("u16", "padding0")
    ]


class IndirectStage(Structure):
    """Material indirect stage structure"""
    MEMBERS = [
        GXTexCoordID("u8", "tex_coord_gen"),
        GXTexMapID("u8", "tex_map"),
        GXIndTexScale("u8", "scale_s"),
        GXIndTexScale("u8", "scale_t")
    ]


class MAT1Block(BlockBase):
    """Material block"""

    SIGNATURE = "mat1"
    MAX_NAME_LEN = 20

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        # Name
        assert "name" in res, "Material is missing name."
        self.name = res["name"]

        # Material name limited to 20 char buffer (null-terminated)
        if len(self.name) > self.MAX_NAME_LEN - 1:
            print(
                f"[WARN] Material name {self.name} is too long. It will be truncated to 19 characters (+1 for null terminator)")

        # TEV colors
        self.tev_col0 = ColorS10.from_list(
            res.get("tev_col0", [0, 0, 0, 0]))
        self.tev_col1 = ColorS10.from_list(
            res.get("tev_col1", [0, 0, 0, 0]))
        self.tev_col2 = ColorS10.from_list(
            res.get("tev_col2", [0, 0, 0, 0]))

        # TEVK colors
        self.tev_kcol0 = Color.from_list(
            res.get("tev_kcol0", [0, 0, 0, 0]))
        self.tev_kcol1 = Color.from_list(
            res.get("tev_kcol1", [0, 0, 0, 0]))
        self.tev_kcol2 = Color.from_list(
            res.get("tev_kcol2", [0, 0, 0, 0]))
        self.tev_kcol3 = Color.from_list(
            res.get("tev_kcol3", [0, 0, 0, 0]))

        # GX bitfield
        self.bit_gx_nums = res.get("bit_gx_nums", 0)

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += 20  # char name[20]

        bsize += 8  # GXColorS10 tev_col0
        bsize += 8  # GXColorS10 tev_col1
        bsize += 8  # GXColorS10 tev_col2

        bsize += 4  # GXColor tev_kcol0
        bsize += 4  # GXColor tev_kcol1
        bsize += 4  # GXColor tev_kcol2
        bsize += 4  # GXColor tev_kcol3

        bsize += 4  # u32 bit_gx_nums

        return bsize

    def write(self, strm: OutputStream):
        """Write block buffer to stream"""
        super.write(self, strm)

        # Material name
        strm.write_string_sz(self.name, self.MAX_NAME_LEN - 1)

        # TEV colors
        self.tev_col0.write(strm)
        self.tev_col1.write(strm)
        self.tev_col2.write(strm)

        # TEVK colors
        self.tev_kcol0.write(strm)
        self.tev_kcol1.write(strm)
        self.tev_kcol2.write(strm)
        self.tev_kcol3.write(strm)

        # GX bitfield
        strm.write_u32(self.bit_gx_nums)

        # Align block to 32B
        self.write_align(strm)
