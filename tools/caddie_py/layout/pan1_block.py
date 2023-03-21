from caddie_py.binary.types.primitive import Primitive
from caddie_py.binary.types.common import VEC3, VEC2, Size
from caddie_py.binary.types.string import String
from caddie_py.binary.block.block_base import BlockBase


class PAN1Block(BlockBase):
    """Pane block"""

    SIGNATURE = "pan1"

    MAX_NAME_LEN = 16
    MAX_USERDATA_LEN = 8

    def __init__(self, res):
        super().__init__(self.SIGNATURE)
        self.children = []

        assert "name" in res, "Pane is missing name"

        self.add_member(Primitive("u8", "visible", value=res.get("visible")))
        # TODO: Make Flag class from Enum
        self.add_member(Primitive("u8", "flags", value=res.get("flags")))
        self.add_member(Primitive("u8", "base_position",
                        value=res.get("base_position")))
        self.add_member(Primitive("u8", "alpha", value=res.get("alpha")))
        self.add_member(Primitive("u8", "padding0"))

        self.add_member(String("name", value=res.get("name"),
                        c_style=True, maxlen=self.MAX_NAME_LEN))
        self.add_member(String("user_data", value=res.get("user_data"),
                        c_style=True, maxlen=self.MAX_USERDATA_LEN))

        self.add_member(VEC3("translate", values=res.get("translate")))
        self.add_member(VEC3("rotate", values=res.get("rotate")))
        self.add_member(VEC2("scale", values=res.get("scale")))
        self.add_member(Size("size", values=res.get("size")))

    def append_child(pane: "PAN1Block"):
        """Append child pane"""
        pass
