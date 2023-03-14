from ..binary import BinaryBlock, BinaryHeaderBlock


class CLYTBlock(BinaryHeaderBlock):
    """Layout header block"""

    # Update as format is revised
    SIGNATURE = "CLYT"
    VERSION = 0x0100  # 1.0

    def __init__(self, blocks: list[BinaryBlock] = []):
        super().__init__(self.SIGNATURE, self.VERSION, list)
