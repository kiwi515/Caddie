from stream.stream_base import StreamBase
from re import search


class Member:
    """Representation of a structure field/member"""

    PRIM_2_WRITE_FUNC = {
        "u8": StreamBase.write_u8,
        "unsigned char": StreamBase.write_u8,

        "s8": StreamBase.write_s8,
        "char": StreamBase.write_s8,
        "signed char": StreamBase.write_s8,

        "u16": StreamBase.write_u16,
        "unsigned short": StreamBase.write_u16,
        "wchar_t": StreamBase.write_u16,

        "s16": StreamBase.write_s16,
        "short": StreamBase.write_s16,
        "signed short": StreamBase.write_s16,

        "u32": StreamBase.write_u32,
        "unsigned long": StreamBase.write_u32,

        "s32": StreamBase.write_s32,
        "long": StreamBase.write_s32,
        "signed long": StreamBase.write_s32,
        "int": StreamBase.write_s32,
        "signed int": StreamBase.write_s32,

        "f32": StreamBase.write_f32,
        "float": StreamBase.write_f32,

        "f64": StreamBase.write_f64,
        "double": StreamBase.write_f64,
    }

    ARRAY_REGEX = r"\[(?P<Size>[0-9]+)\]"

    def __init__(self, type: str, name: str):
        self.type = type
        self.name = name
        self.length = 1
        self.value = None

        # Optional array specification
        match_obj = search(self.ARRAY_REGEX, self.name)
        if match_obj != None:
            self.length = match_obj.group("Size")

        # Limit array length to 1
        self.length = max(1, self.length)

    def set_value(self, data):
        """Set member value"""

        # Is an array
        if self.length > 1:
            assert isinstance(
                data, list), "Cannot set non-array value to array member"
            assert len(
                data) == self.length, f"Array length mismatch: got {len(data)}, expected {self.length}"
        # Not an array
        else:
            assert not isinstance(
                data, list), "Cannot set array value to non-array member"

        self.value = data

    def write(self, strm: StreamBase):
        """Write member to stream"""
        # Primitive type
        if self.type in self.PRIM_2_WRITE_FUNC:
            self.__write_prim(strm)
        # Non-primitive type
        else:
            self.__write(strm)

    def __write_prim(self, strm: StreamBase):
        f = self.PRIM_2_WRITE_FUNC[self.type]

        # Is an array
        if self.length > 1:
            for elem in self.value:
                f(strm, elem)
        # Not an array
        else:
            f(strm, self.value)

    def __write(self, strm: StreamBase):
        # ANSI string, C-style (null terminated)
        if self.type == "cstr":
            strm.write_string(self.value)

        # ANSI string
        elif self.type == "str":
            strm.write_string(self.value, terminate=False)

        # UTF-16 string, C-style (null terminated)
        elif self.type == "cwstr":
            strm.write_wstring(self.value)

        # UTF-16 string
        elif self.type == "wstr":
            strm.write_wstring(self.value, terminate=False)

        # Whatever type this is, it isn't supported yet
        else:
            raise NotImplementedError(
                "Non-primitive, non-string types not yet supported")
