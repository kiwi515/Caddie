from caddie_py.binary.block.block_base import BlockBase
from caddie_py.stream.stream_base import StreamBase
from caddie_py.binary.types.member import Member


class HeaderBlockBase(BlockBase):
    """Base header block"""

    def __init__(self, kind: str, version: int, blocks: list[BlockBase]):
        super().__init__(kind)
        self.version = version
        self.children = blocks

        self.add_member(Member("u16", "version", value=self.VERSION))
        self.add_member(Member("u16", "numBlocks", value=len(self.children)))

    def append_child(self, block: BlockBase):
        """Append child block"""
        self.children.append(block)
        self["numBlocks"].value += 1

    def write(self, strm: StreamBase):
        """Write block buffer to stream"""
        BlockBase.write(self, strm)

        # Children blocks
        for block in self.children:
            block.write(strm)
