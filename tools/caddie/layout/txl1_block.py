from ..binary import BinaryBlock
from ..stream import OutputStream


class TXL1Block(BinaryBlock):
    """Texture list block"""

    SIGNATURE = "txl1"

    def __init__(self, filenames: list[str] = []):
        super().__init__(self.SIGNATURE)
        self.filenames = dict()
        self.pool_size = 0

        for filename in filenames:
            self.add_filename(filename)

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += self.pool_size  # Total pool size

        return bsize

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # Filename count
        strm.write_u16(len(self.filenames))
        # Padding
        strm.write_padding(2)

        # String pool base
        pool_base = 0
        pool_base += super.byte_size()
        pool_base += 2  # u16 numEntries
        pool_base += 2  # u16 padding
        pool_base += 8 * len(self.pool)

        # Filename offsets
        for offset in self.pool.values():
            # Convert pool-relative offset to block-relative offset
            strm.write_u32(pool_base + offset)
            strm.write_padding(4)

        # Filename pool
        for filename in self.pool.keys():
            strm.write_string(filename)

        # Align block to 32B
        self.write_align(strm)

    def add_filename(self, filename: str):
        """Add filename to pool"""
        # String deduplication
        if filename not in self.pool:
            self.pool[filename] = self.pool_size
            self.pool_size += len(filename) + 1

    def find_filename(self, filename: str) -> int:
        """Get filename offset into the pool"""
        assert filename in self.pool, "Failed to find filename"
        return self.pool[filename]
