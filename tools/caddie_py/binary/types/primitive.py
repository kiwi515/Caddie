from caddie_py.binary.types.member import Member
from caddie_py.stream.stream_base import StreamBase


class Primitive(Member):
    """Primitive-type member"""
    PRIM_2_WRITE_FUNC = {
        "u8": StreamBase.write_u8,
        "unsigned char": StreamBase.write_u8,
        "bool": StreamBase.write_u8,

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

    PRIM_2_BYTE_SIZE = {
        "u8": 1,
        "unsigned char": 1,
        "bool": 1,

        "s8": 1,
        "char": 1,
        "signed char": 1,

        "u16": 2,
        "unsigned short": 2,
        "wchar_t": 2,

        "s16": 2,
        "short": 2,
        "signed short": 2,

        "u32": 4,
        "unsigned long": 4,

        "s32": 4,
        "long": 4,
        "signed long": 4,
        "int": 4,
        "signed int": 4,

        "f32": 4,
        "float": 4,

        "f64": 8,
        "double": 8,
    }

    STRING_TYPES = ("cstr", "str", "wcstr", "wstr")

    def __init__(self, _type: str, name: str, arr: str = None, value=None):
        super().__init__(_type, name, arr, value)

        # Attempt to use default primitive value if nothing was specified
        if self.value == None:
            self.value = self.__get_default_value()

    def byte_size(self):
        """Size of primitive member in bytes"""
        # Actually *primitive*
        if self.type in self.PRIM_2_BYTE_SIZE:
            return self.PRIM_2_BYTE_SIZE[self.type]

        # String type
        elif self.type in self.STRING_TYPES:
            x = self.value
            return {
                "str": len(x),
                "cstr": len(x) + 1,
                "wstr": len(x) * 2,
                "wcstr": (len(x) + 1) * 2,
            }[self.type]

        else:
            assert False, f"Unsupported non-primitive type: {self.type}"

    def write(self, strm: StreamBase):
        """Write primitive member to stream"""
        # Primitive type
        if self.type in self.PRIM_2_WRITE_FUNC:
            self.__write_prim(strm)
        # String type
        elif self.type in self.STRING_TYPES:
            self.__write_string(strm)
        # IDK man
        else:
            assert False, f"Unsupported primitive type: {self.type}"

    def __write_prim(self, strm: StreamBase):
        """Write primitive member to stream"""
        f = self.PRIM_2_WRITE_FUNC[self.type]

        # Member is an array
        if self.is_array():
            self.__write_array(strm, f)
        # Not an array
        else:
            f(strm, self.value)

    def __write_string(self, strm: StreamBase):
        """Write string member to stream"""

        # Write function
        f = StreamBase.write_wstring if self.type.startswith(
            "w") else StreamBase.write_string

        # Null-termination
        terminate = "cstr" in self.type

        maxlen = -1

        if self.is_array():
            self.__write_array(strm, f, maxlen, terminate)
        else:
            f(strm, self.value, maxlen, terminate)

    def __write_array(self, strm: StreamBase, f, *argv):
        """Write primitive member as array, using the specified write function"""
        assert self.is_array(), "Member is not an array"

        # Variable length array
        if self.is_vl_array():
            for elem in self.value:
                f(strm, elem, *argv)
        # Array of explicit length
        else:
            for i in range(self.__length):
                f(strm, self.value[i], *argv)

    def __get_default_value(self):
        """Get default value for primitive member"""
        # Variable-length array
        if self.is_vl_array():
            # Cannot safely initialize, user doesn't know length
            return []

        default = None

        # Primitive/simple type
        if self.type in self.PRIM_2_WRITE_FUNC:
            default = 0
        # String type
        elif self.type in self.STRING_TYPES:
            default = ""
        # Unsupported type, or is a Structure
        else:
            print(
                f"[WARN] Primitive type has no known default value: {self.type}")
            return None

        # Scale for arrays
        if self.is_array():
            return [default * self.__length]

        # Single element
        return default
