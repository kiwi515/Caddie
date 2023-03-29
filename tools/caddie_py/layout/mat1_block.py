from caddie_py.binary.block.block_base import BlockBase
from caddie_py.layout.pan1_block import PaneRes
from caddie_py.binary.types.structure import Structure
from caddie_py.binary.types.primitive import Primitive
from caddie_py.binary.types.bitfield import BitField, BitMember
from caddie_py.binary.types.string import String
from caddie_py.binary.types.common import VEC2
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
        Primitive("u8[2]", "padding0")
    ]


class TexSRT(Structure):
    """Texture S/R/T (Scale/Rotate/Translate)"""

    MEMBERS = [
        VEC2("translate"),
        Primitive("f32", "rotate"),
        VEC2("scale")
    ]


class IndirectStage(Structure):
    """Material indirect stage structure"""

    MEMBERS = [
        GXTexCoordID("u8", "tex_coord_gen"),
        GXTexMapID("u8", "tex_map"),
        GXIndTexScale("u8", "scale_s"),
        GXIndTexScale("u8", "scale_t")
    ]


class BitGXNums(BitField):
    """GX "nums" bitfield"""

    MEMBERS = [
        BitMember("num_tex_map", 4),
        BitMember("num_tex_srt", 4),
        BitMember("num_tex_coord_gen", 4),
        BitMember("num_ind_srt", 2),
        BitMember("num_ind_stage", 3),
        BitMember("has_tev_swap", 1),
        BitMember("num_tev_stage", 5),
        BitMember("has_chan_ctrl", 1),
        BitMember("has_mat_color", 1),
        BitMember("has_alpha_comp", 1),
        BitMember("has_blend_mode", 1)
    ]


class MaterialRes(Structure):
    """Material structure"""

    MAX_NAME_LEN = 20
    TEV_REG_MAX = 3
    KCOLOR_MAX = 4

    # TODO: Add optional members somehow (toggled by BitGXNums)
    MEMBERS = PaneRes.MEMBERS + [
        String("mat_name", c_style=False, maxlen=MAX_NAME_LEN),
        GXColorS10("tev_colors", arr=f"[{TEV_REG_MAX}]"),
        GXColor("tev_k_colors", arr=f"[{KCOLOR_MAX}]"),
        BitGXNums("u32", "bit_gx_nums")
    ]


class MaterialDesc(Structure):
    """Material descriptor structure"""

    MEMBERS = [
        Primitive("u32", "offset"),
        Primitive("u8", "padding0", arr="[4]")
    ]


class MAT1Block(BlockBase):
    """Material block"""

    SIGNATURE = "mat1"

    def __init__(self, list_res):
        super().__init__(self.SIGNATURE)
        self.__pool_size = 0

        self.add_member(Primitive("u16", "numEntries", value=len(list_res)))
        self.add_member(Primitive("u8", "padding0", arr="[2]"))
        self.add_member(MaterialDesc("matDescs", arr="[]"))
        self.add_member(MaterialRes("materials", arr="[]"))

        for res in list_res:
            self.add_material(res)

    # TODO
    def add_material(self, res):
        """Add material to list"""
        # Add material
        mat = MaterialRes("", values=res)
        self["materials"].append(mat)

        # Add new material descriptor
        desc = MaterialDesc("", values={"offset": self.__pool_size})
        self["matDescs"].append(desc)

        # Increase material count
        self["numEntries"].value += 1

        # Update pool size
        self.__pool_size += mat.byte_size()
        pass
