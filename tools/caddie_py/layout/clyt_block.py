from caddie_py.binary.block.block_base import BlockBase
from caddie_py.binary.block.header_block_base import HeaderBlockBase


class CLYTBlock(HeaderBlockBase):
    """Layout header block"""

    # Update as format is revised
    SIGNATURE = "CLYT"
    VERSION = 0x0100  # 1.0

    def __init__(self, blocks: list[BlockBase] = []):
        super().__init__(self.SIGNATURE, self.VERSION, blocks)
