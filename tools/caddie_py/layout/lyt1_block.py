from caddie_py.binary.block.block_base import BlockBase


class LYT1Block(BlockBase):
    """Layout block"""

    SIGNATURE = "lyt1"

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        # Extract from JSON
        self.add_member("bool", "centered", res.get("centered"))
        self.add_member("u8[3]", "padding0")
        self.add_member("f32[2]", "size", res.get("size"))
