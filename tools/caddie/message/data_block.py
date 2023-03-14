from ..binary import BinaryBlock, BinaryHeaderBlock
from ..stream import OutputStream


class DATABlock(BinaryBlock):
    """Message data (pool) block"""

    SIGNATURE = "DATA"

    def __init__(self, messages: list[str]):
        super().__init__(self.SIGNATURE)
        self.messages = messages

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        for msg in self.messages:
            msg_len = len(msg) + 1
            bsize += msg_len * 2  # wchar_t

        return bsize

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # Message pool data
        for msg in self.messages:
            strm.write_wstring(msg)

        # Align block to 32B
        self.write_align(strm)
