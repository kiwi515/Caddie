"""File stream classes with configurable endianness (byteorder).
    """

from dataclasses import dataclass
from struct import pack


class StreamEndian:
    # Endianness
    LITTLE = 0
    BIG = 1
    MAX = 2


class StreamSeekPos:
    # Seek type
    BEGIN = 0
    CURRENT = 1
    END = 2
    MAX = 3


@dataclass
class InputStream:
    endian: int
    pos: int
    _size: int
    data: bytes

    def __init__(self, _data: bytes, _endian: int):
        """Constructor
            _data (bytes): File data
            _endian (int): Target endianness (LITTLE / BIG)
        """
        assert _endian >= StreamEndian.LITTLE and _endian < StreamEndian.MAX
        self.endian = _endian
        self.pos = 0
        self._size = len(_data)
        self.data = _data

    @staticmethod
    def open_file(path: str, _endian: int) -> "InputStream":
        """Construct an input stream for the file at the specified path,
        using the specified endianness."""
        with open(path, "rb") as f:
            return InputStream(f.read(), _endian)

    def eof(self) -> bool:
        """Check if the stream has hit the end of the file."""
        return self.pos >= len(self.data)

    def read(self, size: int) -> bytearray:
        """Read bytes from the stream."""
        assert self.pos + size <= len(self.data)
        data = self.data[self.pos: self.pos + size]
        self.pos += size
        return data

    def seek(self, ofs: int, whence: int):
        """Seek the stream position."""
        if whence == StreamSeekPos.BEGIN:
            self.pos = ofs
        elif whence == StreamSeekPos.CURRENT:
            self.pos = self.pos + ofs
        elif whence == StreamSeekPos.END:
            self.pos = self._size - ofs
        else:
            assert False, "Invalid seek whence"
        # Clamp position to before EOF
        self.pos = min(self.pos, self._size - 1)

    def get_s8(self) -> int:
        """Read a signed 8-bit integer from the stream."""
        return self._from_bytes(self.read(1), True)

    def get_u8(self) -> int:
        """Read an unsigned 8-bit integer from the stream."""
        return self._from_bytes(self.read(1), False)

    def get_s16(self) -> int:
        """Read a signed 16-bit integer from the stream."""
        return self._from_bytes(self.read(2), True)

    def get_u16(self) -> int:
        """Read an unsigned 16-bit integer from the stream."""
        return self._from_bytes(self.read(2), False)

    def get_s32(self) -> int:
        """Read a signed 32-bit integer from the stream."""
        return self._from_bytes(self.read(4), True)

    def get_u32(self) -> int:
        """Read an unsigned 32-bit integer from the stream."""
        return self._from_bytes(self.read(4), False)

    def get_string(self) -> str:
        """Read a string from the stream."""
        string = ""
        c = self.get_s8()
        while c != 0x00:
            string += chr(c)
            c = self.get_s8()
        return string

    def get_string_sz(self, sz: int) -> str:
        """Read a string of size 'sz' from the stream."""
        string = ""
        while sz > 0:
            c = self.get_s8()
            string += chr(c)
            sz -= 1
        return string

    def _from_bytes(self, data: bytes, _signed: bool) -> int:
        """Convert bytes from the stream into an integer"""
        endian_str = ("little", "big")[self.endian]
        return int.from_bytes(data, byteorder=endian_str, signed=_signed)


@dataclass
class OutputStream():
    endian: int

    def __init__(self, path: str, _endian: int):
        """Constructor
            path (str): File path
            _endian (int): Target endianness (ENDIAN_LITTLE / ENDIAN_BIG)
        """
        assert _endian >= StreamEndian.LITTLE and _endian < StreamEndian.MAX
        self.endian = _endian
        self.writer = open(path, "wb+")

    def close(self):
        self.writer.close()

    def write(self, data: bytes):
        """Write bytes to the stream."""
        self.writer.write(data)

    def write_padding(self, size: int):
        """Write padding to the stream."""
        self.writer.write(bytes([0x00] * size))

    def write_s8(self, data: int):
        """Write a signed 8-bit integer to the stream."""
        self.writer.write(self._to_bytes(data, 1, True))

    def write_u8(self, data: int):
        """Write a unsigned 8-bit integer to the stream."""
        self.writer.write(self._to_bytes(data, 1, False))

    def write_s16(self, data: int):
        """Write a signed 16-bit integer to the stream."""
        self.writer.write(self._to_bytes(data, 2, True))

    def write_u16(self, data: int):
        """Write a unsigned 16-bit integer to the stream."""
        self.writer.write(self._to_bytes(data, 2, False))

    def write_s32(self, data: int):
        """Write a signed 32-bit integer to the stream."""
        self.writer.write(self._to_bytes(data, 4, True))

    def write_u32(self, data: int):
        """Write a unsigned 32-bit integer to the stream."""
        self.writer.write(self._to_bytes(data, 4, False))

    def write_float(self, data: float):
        """Write a float to the stream."""
        self.writer.write(self._flt_to_bytes(data))

    def write_string(self, data: str):
        """Write a string to the stream."""
        for ch in data:
            self.write_s8(ord(ch))
        self.write_s8(0x00)

    def write_wstring(self, data: str):
        """Write a widechar (UTF-16) string to the stream."""
        self.write(data.encode("utf-16be"))
        self.write_u16(0x0000)

    def write_string_sz(self, data: str, sz: int):
        """Write a string of size sz to the stream."""
        sz = min(len(data), sz)
        for i in range(sz):
            self.write_s8(ord(data[i]))

    def _to_bytes(self, data: int, size: int, _signed: bool) -> bytes:
        """Convert integer value into bytes"""
        endian_str = ("little", "big")[self.endian]
        return int.to_bytes(data, length=size, byteorder=endian_str, signed=_signed)

    def _flt_to_bytes(self, data: float) -> bytes:
        arr = pack("f", data)
        return bytes(arr)
