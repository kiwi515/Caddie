from stream_base import StreamBase, SeekOrigin


class OpenMode:
    Read, Write, Max = range(3)


class DataMode:
    Text, Binary, Max = range(3)


class FileStream(StreamBase):
    """File stream"""

    def __init__(self, endian: int):
        super.__init__(endian)
        self.path = None
        self.open_mode = None
        self.data_mode = None
        self.file = None

    def read(self, size: int) -> bytes:
        """Read bytes from stream"""
        assert not self.eof(), "End-of-file while reading"
        assert self.open_mode == OpenMode.Read, "Not for this openmode"

        # No file open
        if self.file == None:
            return bytes()

        return self.file.read(size)

    def write(self, data: bytes):
        """Write bytes to stream"""
        assert not self.eof(), "End-of-file while writing"
        assert self.open_mode == OpenMode.Write, "Not for this openmode"

        # No file open
        if self.file == None:
            return

        self.file.write(data)

    def eof(self) -> bool:
        """Check whether the stream has hit the end-of-file"""
        if self.open_mode == OpenMode.Read:
            return not self.file.readable()
        elif self.open_mode == OpenMode.Write:
            return not self.file.writable()

        return False

    def seek(self, origin: int, offset: int):
        """Seek the stream position"""
        assert origin >= 0 and origin < SeekOrigin.Max

        # No file open
        if self.file == None:
            return

        self.file.seek(offset, origin)

    def open(self, path: str, open_mode: int, data_mode: int):
        """Open stream to file"""
        assert open_mode >= 0 and open_mode < OpenMode.Max
        assert data_mode >= 0 and data_mode < DataMode.Max

        # Close existing file
        if self.file != None:
            self.close()

        self.path = path
        self.open_mode = open_mode
        self.data_mode = data_mode

        self.file = open(self.path, self.__get_py_open_mode())

    def close(self):
        """Close stream"""
        if self.file != None:
            self.file.close()
            self.file = None

    def __get_py_open_mode(self) -> str:
        """Get openmode string based on stream setup"""
        # Read/write mode
        mode = ("r", "w")[self.open_mode]

        # Binary data
        if self.data_mode == DataMode.Binary:
            mode += "b"

        return mode
