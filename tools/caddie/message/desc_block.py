from ..binary import BinaryBlock
from ..stream import OutputStream
from data_block import DATABlock


class DESCBlock(BinaryBlock):
    """Message descriptor block"""

    SIGNATURE = "DESC"

    def __init__(self, offsets: list[int]):
        super().__init__(self.SIGNATURE)
        self.offsets = offsets

    @classmethod
    def from_data_block(block: DATABlock):
        """Generate DESC block from message data"""
        offsets = []
        offset_now = 0
        for msg in block.messages:
            offsets.append(offset_now)
            msg_len = len(msg) + 1
            offset_now += msg_len * 2  # wchar_t
        return DESCBlock(offsets)

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += 4  # u32 numMsg
        bsize += len(self.offsets) * 4  # u32 offsets[]

        return bsize

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # Message count
        strm.write_u32(len(self.offsets))
        # Message pool offsets
        for ofs in self.offsets:
            strm.write_u32(ofs)

        # Align block to 32B
        self.write_align(strm)
