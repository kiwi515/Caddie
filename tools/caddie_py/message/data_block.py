from caddie_py.binary.block.block_base import BlockBase
from caddie_py.binary.member import Member


class DATABlock(BlockBase):
    """Message data (pool) block"""

    SIGNATURE = "DATA"

    def __init__(self, messages: list[str] = []):
        super().__init__(self.SIGNATURE)

        self.add_member("wcstr[]", "messages", messages)

    def add_message(self, message: str):
        """Add message string to block"""
        self["messages"].value.append(message)
