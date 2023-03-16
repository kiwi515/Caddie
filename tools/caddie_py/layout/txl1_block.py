from caddie_py.binary.block.pool_block import PoolBlock


class TXL1Block(PoolBlock):
    """Texture list block"""

    SIGNATURE = "txl1"

    def __init__(self, filenames: list[str] = []):
        super().__init__(self.SIGNATURE, "cstr", filenames)

        self.add_member("u16", "numEntries", len(self["pool"]))
        self.add_member("u16", "padding0")
