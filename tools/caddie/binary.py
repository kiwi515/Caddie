from .stream import OutputStream

# All blocks are aligned to 32 bytes
BLOCK_ALIGN = 32


class BinaryBlock:
    """Base block class"""

    def __init__(self, kind: str):
        self.block_kind = kind

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += 4  # u32 kind
        bsize += 4  # u32 size
        return bsize

    def aligned_byte_size(self) -> int:
        """Get aligned size of block in bytes"""
        bsize = self.byte_size()
        return bsize + BinaryBlock.align_required(bsize, BLOCK_ALIGN)

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        # Block signature
        strm.write_string_sz(self.block_kind, 4)
        # Block size (blocks are 32B aligned)
        strm.write_u32(self.aligned_byte_size())

    def write_align(self, strm: OutputStream):
        """Write padding to align block contents"""
        strm.write_padding(self.aligned_byte_size() - self.byte_size())

    @staticmethod
    def align_required(size: int, align: int) -> int:
        """Determine how much padding is required to align the block"""
        return align - (size % align)


class BinaryHeaderBlock(BinaryBlock):
    """Base header block"""

    def __init__(self, kind: str, version: int, blocks: list[BinaryBlock]):
        super().__init__(kind)
        self.version = version
        self.blocks = blocks

    def add_block(self, block: BinaryBlock):
        """Append child block"""
        self.blocks.append(block)

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.calc_size(self)

        bsize += 2  # u16 version
        bsize += 2  # u16 numBlocks

        # Child block size
        for block in self.blocks:
            bsize += block.byte_size()

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # File version
        strm.write_u16(self.version)
        # BinaryBlock count
        strm.write_u16(len(self.blocks))

        # Align block to 32B
        self.write_align(strm)

        # Write children blocks
        for block in self.blocks:
            block.write(strm)
