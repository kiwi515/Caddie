from ..binary import BlockBase, HeaderBlockBase


class CLYTBlock(HeaderBlockBase):
    """Layout header block"""

    # Update as format is revised
    SIGNATURE = "CLYT"
    VERSION = 0x0100  # 1.0

    def __init__(self, blocks: list[BlockBase] = []):
        super().__init__(self.SIGNATURE, self.VERSION, blocks)
