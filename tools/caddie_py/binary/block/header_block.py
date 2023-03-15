from block_base import BlockBase
from stream.stream_base import StreamBase


class HeaderBlockBase(BlockBase):
    """Base header block"""

    def __init__(self, kind: str, version: int, blocks: list[BlockBase]):
        super().__init__(kind)
        self.version = version
        self.children = blocks

    def append_child(self, block: BlockBase):
        """Append child block"""
        self.children.append(block)

    def write(self, strm: StreamBase):
        """Write block buffer to stream"""
        super.write(self, strm)

        # Children blocks
        for block in self.children:
            block.write(block, strm)
