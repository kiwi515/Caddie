from ..binary.block.block_base import BlockBase
from ..binary.block.header_block import HeaderBlockBase


class CMSGBlock(HeaderBlockBase):
    """Message header block"""

    # Update as format is revised
    SIGNATURE = "CMSG"
    VERSION = 0x0100  # 1.0

    def __init__(self, blocks: list[BlockBase] = []):
        super().__init__(self.SIGNATURE, self.VERSION, blocks)
