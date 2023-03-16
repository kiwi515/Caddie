from caddie_py.binary.block.block_base import BlockBase
from caddie_py.binary.types.member import Member


class PoolBlock(BlockBase):
    """Data pool block"""

    def __init__(self, kind: str, pool_type: str, data: list = []):
        super().__init__(kind)
        self.add_member(Member(pool_type, "pool", arr="[]", value=data))

    def add_data(self, data):
        """Add data to pool"""
        self["pool"].value.append(data)
