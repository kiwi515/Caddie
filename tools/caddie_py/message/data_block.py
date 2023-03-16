from caddie_py.binary.block.pool_block import PoolBlock


class DATABlock(PoolBlock):
    """Message data (pool) block"""

    SIGNATURE = "DATA"

    def __init__(self, messages: list[str] = []):
        super().__init__(self.SIGNATURE, "wcstr", messages)
