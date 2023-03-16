from caddie_py.binary.block.block_base import BlockBase
from caddie_py.message.data_block import DATABlock


class DESCBlock(BlockBase):
    """Message descriptor block"""

    SIGNATURE = "DESC"

    def __init__(self, offsets: list[int] = []):
        super().__init__(self.SIGNATURE)

        self.add_member("u32", "numMsg", len(offsets))
        self.add_member("u32[]", "msgOffsets", offsets)

    def add_offset(self, offset: int):
        """Add message offset to block"""
        self["numMsg"].value += 1
        self["msgOffsets"].value.append(offset)

    @staticmethod
    def from_data_block(block: DATABlock):
        """Generate DESC block from message data"""
        offsets = []
        offset_now = 0

        for msg in block["pool"].value:
            offsets.append(offset_now)
            # +1 for null terminator, x2 for wchar_t
            offset_now += (len(msg) + 1) * 2

        return DESCBlock(offsets)
