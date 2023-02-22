from .stream import OutputStream


class Block:
    """Base block class"""

    def __init__(self, kind: str):
        self.kind = kind
        self.size = -1

    def calc_size(self):
        """Calculate block size (self.size)"""
        pass

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        # Calculate block size
        self.calc_size()
        # Block signature
        strm.write_string_sz(self.kind, 4)
        # Block size (blocks are 32B aligned)
        self.align_size = self.size + self.align_required(self.size, 32)
        strm.write_u32(self.align_size)

    def write_align(self, strm: OutputStream):
        """Write padding to align block contents"""
        strm.write(bytes([0x00] * (self.align_size - self.size)))

    @staticmethod
    def align_required(size: int, align: int):
        """Determine how much padding is required to align the block"""
        return align - (size % align)


class CMSGBlock(Block):
    """Header block"""

    # Update as format is revised
    SIGNATURE = "CMSG"
    VERSION = 0x0100  # 1.0

    def __init__(self, blocks: list[Block]):
        super().__init__(self.SIGNATURE)
        self.blocks = blocks

    def calc_size(self):
        """Calculate block size (self.size)"""
        # Calculate size of child blocks
        for block in self.blocks:
            block.calc_size()

        self.size = 0
        self.size += 4  # u32 kind
        self.size += 4  # u32 size
        self.size += 2  # u16 version
        self.size += 2  # u16 numBlocks

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        Block.write(self, strm)

        # File version
        strm.write_u16(self.VERSION)
        # Block count
        strm.write_u16(len(self.blocks))

        # Align block to 32B
        self.write_align(strm)

        # Write children blocks
        for block in self.blocks:
            block.write(strm)


class DESCBlock(Block):
    """Message descriptor block"""
    SIGNATURE = "DESC"

    def __init__(self, offsets: list[int]):
        super().__init__(self.SIGNATURE)
        self.offsets = offsets

    def calc_size(self):
        """Calculate block size (self.size)"""
        self.size = 0
        self.size += 4  # u32 kind
        self.size += 4  # u32 size
        self.size += 4  # u32 numMsg
        self.size += len(self.offsets) * 4  # u32 offsets[]

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        Block.write(self, strm)

        # Message count
        strm.write_u32(len(self.offsets))
        # Message pool offsets
        for ofs in self.offsets:
            strm.write_u32(ofs)

        # Align block to 32B
        self.write_align(strm)


class DATABlock(Block):
    """Message data (pool) block"""
    SIGNATURE = "DATA"

    def __init__(self, messages: list[str]):
        super().__init__(self.SIGNATURE)
        self.messages = messages

    def calc_size(self):
        """Calculate block size (self.size)"""
        self.size = 0
        self.size += 4  # u32 kind
        self.size += 4  # u32 size
        self.size += sum((len(msg) + 1) * 2
                         for msg in self.messages)  # char data[]

    def gen_desc(self) -> DESCBlock:
        """Generate DESC block from message data"""
        offsets = []
        offset_now = 0
        for msg in self.messages:
            offsets.append(offset_now)
            offset_now += (len(msg) + 1) * 2
        return DESCBlock(offsets)

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        Block.write(self, strm)

        # Message pool data
        for msg in self.messages:
            strm.write_wstring(msg)

        # Align block to 32B
        self.write_align(strm)
