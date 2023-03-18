from caddie_py.binary.types.member import Member
from caddie_py.stream.stream_base import StreamBase
from caddie_py.utility.util import Util


class String(Member):
    """ANSI string member"""

    STRING_TYPES = ("cstr", "str")

    def __init__(self, name: str, arr: str = None, value=None, c_style: bool = True, maxlen: int = -1):
        super().__init__(self.__class__.__name__, name, arr, value)
        self.c_style = c_style
        self.maxlen = maxlen

    def byte_size(self):
        """Size of string member in bytes"""
        total = 0
        for s in self:
            total += len(s)
            # Null terminator
            if self.c_style:
                total += 1

        return total

    def write(self, strm: StreamBase):
        """Write string member to stream"""
        for string in self:
            if Util.str_len(string, terminator=self.c_style) > self.maxlen:
                print(
                    f"[WARN] String {string} will be truncated to {self.maxlen} characters.")

            strm.write_string(string, self.maxlen, self.c_style)


class WString(String):
    """Widechar (UTF-16) string member"""

    def __init__(self, name: str, arr: str = None, value=None, c_style: bool = True, maxlen: int = -1):
        super().__init__(name, arr, value)
        self.c_style = c_style
        self.maxlen = maxlen

    def byte_size(self):
        """Size of string member in bytes"""
        return String.byte_size() * 2  # wchar_t

    def write(self, strm: StreamBase):
        """Write string member to stream"""
        for string in self:
            # NOT A BUG! Max length counts characters, not bytes
            if Util.str_len(string, terminator=self.c_style) > self.maxlen:
                print(
                    f"[WARN] String {string} will be truncated to {self.maxlen} characters.")

            strm.write_wstring(string, self.maxlen, self.c_style)
