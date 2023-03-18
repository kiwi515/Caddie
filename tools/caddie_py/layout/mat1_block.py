from caddie_py.binary.block.block_base import BlockBase
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
        Primitive("u16", "padding0")
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


class MAT1Block(BlockBase):
    """Material block"""

    SIGNATURE = "mat1"

    MAX_NAME_LEN = 20
    TEV_REG_MAX = 3
    KCOLOR_MAX = 4

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        # Name
        assert "name" in res, "Material is missing name."
        self.add_member(String("name", value=res.get("name"),
                        c_style=False, maxlen=self.MAX_NAME_LEN))

        # TEV colors
        self.add_member(GXColorS10(
            "tev_colors", arr=f"[{self.TEV_REG_MAX}]", values=res.get("tev_colors")))

        # TEVK colors
        self.add_member(GXColor(
            "tev_k_colors", arr=f"[{self.KCOLOR_MAX}]", values=res.get("tev_k_colors")))

        # GX bitfield
        self.add_member(BitField("u32", "bit_gx_nums",
                        values=res.get("bit_gx_nums")))

        # Alpha compare (optional)
        if self["bit_gx_nums"]["has_alpha_comp"].value:
            self.add_member(AlphaCompare("alpha_compare",
                            values=res.get("alpha_compare")))

        # Channel control (optional)
        if self["bit_gx_nums"]["has_chan_ctrl"].value:
            self.add_member(ChanCtrl("chan_ctrl", values=res.get("chan_ctrl")))

        # Indirect SRT(s) (optional)
        num_ind_srt = self["bit_gx_nums"]["num_ind_srt"].value
        if num_ind_srt > 0:
            self.add_member(
                TexSRT("ind_srts", arr=f"[{num_ind_srt}]", values=res.get("ind_srt")))

        # Indirect stage(s) (optional)
        num_ind_stage = self["bit_gx_nums"]["num_ind_stage"].value
        if num_ind_stage > 0:
            self.add_member(IndirectStage(
                "ind_stages", arr=f"[{num_ind_stage}]", values=res.get("ind_srt")))
