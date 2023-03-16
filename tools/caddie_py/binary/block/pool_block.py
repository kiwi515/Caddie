from caddie_py.binary.block.block_base import BlockBase


class PoolBlock(BlockBase):
    """Data pool block"""

    def __init__(self, kind: str, pool_type: str, data: list = []):
        super().__init__(kind)
        self.add_member(f"{pool_type}[]", "pool", data)

    def add_data(self, data):
        """Add data to pool"""
        self["pool"].value.append(data)
