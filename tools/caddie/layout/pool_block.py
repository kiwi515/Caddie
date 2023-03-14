from ..binary import BinaryBlock
from ..stream import OutputStream


class POOLBlock(BinaryBlock):
    """String pool block"""

    SIGNATURE = "POOL"

    def __init__(self, strings: list[str] = []):
        super().__init__(self.SIGNATURE)
        self.pool = dict()
        self.pool_size = 0

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += self.pool_size  # Total pool size

        return bsize

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # String pool
        for string in self.pool.keys():
            strm.write_string(string)

        # Align block to 32B
        self.write_align(strm)

    def add_string(self, string: str):
        """Add string to pool"""
        # String deduplication
        if string not in self.pool:
            self.pool[string] = self.pool_size
            self.pool_size += len(string) + 1

    def find_string(self, string: str) -> int:
        """Get string offset into the pool"""
        assert string in self.pool, "Failed to find string"
        return self.pool[string]
