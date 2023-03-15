from ..binary import BlockBase
from ..binary.member import Member


class DATABlock(BlockBase):
    """Message data (pool) block"""

    SIGNATURE = "DATA"
    MEMBERS =

    def __init__(self, messages: list[str]):
        super().__init__(self.SIGNATURE)
        self.messages = messages
