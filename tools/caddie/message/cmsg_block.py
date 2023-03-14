from ..binary import BinaryBlock, BinaryHeaderBlock


class CMSGBlock(BinaryHeaderBlock):
    """Message header block"""

    # Update as format is revised
    SIGNATURE = "CMSG"
    VERSION = 0x0100  # 1.0

    def __init__(self, blocks: list[BinaryBlock] = []):
        super().__init__(self.SIGNATURE, self.VERSION, blocks)
