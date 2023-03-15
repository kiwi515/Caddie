from stream_base import StreamBase


class BufferStream(StreamBase):
    """Buffer stream"""

    def __init__(self, endian: int):
        super.__init__(endian)
        self.data = None

    def read(self, size: int) -> bytearray:
        """Read bytes from stream"""
        raise NotImplementedError("BufferStream does not yet support reading")

    def write(self, data: bytearray):
        """Write bytes to stream"""

        # No file open
        if self.data == None:
            return

        self.data += data

    def eof(self) -> bool:
        """Check whether the stream has hit the end-of-file"""
        return False

    def seek(self, origin: int, offset: int):
        """Seek the stream position"""
        raise NotImplementedError("BufferStream does not yet support seeking")

    def open(self, data: bytearray = bytearray()):
        """Open stream (no buffer specified = create one)"""
        self.data = data

    def buffer_data(self) -> bytearray:
        """Access buffer data"""
        return self.data

    def buffer_size(self) -> int:
        """Access buffer size"""
        return len(self.data)
