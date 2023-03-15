from stream.buffer_stream import BufferStream
from stream.stream_base import Endian, StreamBase
from member import Member


class BlockBase:
    """Base block class"""

    # All blocks are aligned to 32 bytes
    BLOCK_ALIGN = 32

    # Block magic/kind is limited to 4 bytes
    KIND_MAX_LEN = 4

    def __init__(self, kind: str):
        self.kind = kind
        self.strm = BufferStream(Endian.Big)

    def byte_size(self) -> int:
        """Size of block in bytes"""
        bsize = 0
        bsize += 4  # u32 kind
        bsize += 4  # u32 size
        bsize += self.strm.buffer_size()  # Block data
        return bsize

    def aligned_size(self) -> int:
        """Size of block in bytes, aligned to 32B"""
        bsize = self.byte_size()
        return bsize + self.align_required(bsize, self.BLOCK_ALIGN)

    def append_member(self, member: Member):
        """Write member to buffer"""
        member.write(self.strm)

    def write(self, strm: StreamBase):
        """Write block buffer to stream"""
        # Block kind
        strm.write_string(self.kind, maxlen=self.KIND_MAX_LEN, terminate=False)
        # Block size
        strm.write_u32(self.byte_size())
        # Block data
        strm.write(self.strm.buffer_data())
        # Block padding
        strm.write_padding(self.aligned_size() - self.byte_size())

    @classmethod
    def align_required(size: int, align: int) -> int:
        """Determine how much padding is required to align the block"""
        return align - (size % align)
