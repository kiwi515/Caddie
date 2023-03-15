from ..binary import BlockBase
from txl1_block import TXL1Block


class FNL1Block(TXL1Block):
    """Font name list block"""

    SIGNATURE = "fnl1"

    def __init__(self, filenames: list[str] = []):
        super().__init__(self.SIGNATURE, filenames)
