from caddie_py.stream.block_builder import BlockBuilder
from caddie_py.stream.stream_base import Endian, StreamBase
from caddie_py.binary.member import Member


class BlockBase:
    """Base block class"""

    # All blocks are aligned to 32 bytes
    BLOCK_ALIGN = 32

    # Block magic/kind is limited to 4 bytes
    KIND_MAX_LEN = 4

    def __init__(self, kind: str):
        self.kind = kind
        self.builder = BlockBuilder(Endian.Big)
        self.__members = dict()

    def __getitem__(self, key: str) -> Member:
        """Access block member"""
        assert key in self.__members, f"Member does not exist: {key}"

        return self.__members[key]

    def add_member(self, _type: str, name: str, value=None):
        """Add member to block"""
        assert name not in self.__members, f"Duplicate member declaration: {name}"

        m = Member(_type, name, value)
        self.__members[name] = m

    def byte_size(self) -> int:
        """Size of block in bytes"""
        bsize = 0
        bsize += 4  # u32 kind
        bsize += 4  # u32 size
        bsize += self.builder.buffer_size()  # Block data
        return bsize

    def aligned_size(self) -> int:
        """Size of block in bytes, aligned to BLOCK_ALIGN"""
        bsize = self.byte_size()
        align = self.BLOCK_ALIGN - (bsize % self.BLOCK_ALIGN)
        return bsize + align

    def write(self, strm: StreamBase):
        """Write block builder to stream"""
        # Serialize to block builder
        for m in self.__members.values():
            m.write(self.builder)

        # Block kind
        strm.write_string(self.kind, maxlen=self.KIND_MAX_LEN, terminate=False)
        # Block size
        strm.write_u32(self.aligned_size())
        # Block data
        strm.write(self.builder.buffer_data())
        # Block padding
        strm.write_padding(self.aligned_size() - self.byte_size())
