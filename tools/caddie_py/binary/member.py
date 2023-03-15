from caddie_py.stream.stream_base import StreamBase
from caddie_py.utility.util import Util
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

    ARRAY_REGEX = r"(?P<Type>[0-9a-zA-Z_]+)(\[(?P<Size>[0-9]*)\])?"

    def __init__(self, _type: str, name: str, value=None):
        # Parse type
        match_obj = search(self.ARRAY_REGEX, _type)
        assert match_obj != None, f"Invalid type declaration: {_type}"

        # Type name
        self.type = match_obj.group("Type")

        # Type length (array length)
        if match_obj.group("Size") != None:
            self.length = match_obj.group("Size")

            # Variadic-length array
            if self.length == "":
                self.length = -1
            else:
                # Limit array length to 1
                self.length = max(1, self.length)
        else:
            # Single element
            self.length = 1

        # Member name
        self.name = name
        # Member value
        self.set_value(value)

    def __repr__(self):
        """Convert object to string (for debugging)"""
        text = f"{self.type} {self.name}"

        # Format array type
        if self.is_array():
            # Variable-length array
            if self.is_vl_array():
                text += "[]"
            # Explicit length
            else:
                text += f"[{self.length}]"

        return f"{text} = {self.value}"

    def set_value(self, data):
        """Set member value"""
        # Is an array
        if self.is_array():
            assert Util.is_iterable(
                data), "Cannot set non-array value to array member"

            # Explicit array length
            if not self.is_vl_array():
                assert len(
                    data) == self.length, f"Array length mismatch: got {len(data)}, expected {self.length}"

            # Convert all iterable types to list
            self.value = list(data)

        # Not an array
        else:
            assert not Util.is_iterable(
                data), "Cannot set array value to non-array member"
            self.value = data

    def write(self, strm: StreamBase):
        """Write member to stream"""
        # Primitive type
        if self.type in self.PRIM_2_WRITE_FUNC:
            self.__write_prim(strm)
        # Non-primitive type
        else:
            self.__write_non_prim(strm)

    def is_array(self):
        """Check whether the member is an array"""
        return self.length == -1 or self.length > 1

    def is_vl_array(self):
        """Check whether the member is a variable-length array"""
        return self.length == -1

    def __write_prim(self, strm: StreamBase):
        """Write primitive member to stream"""
        f = self.PRIM_2_WRITE_FUNC[self.type]

        # Member is an array
        if self.is_array():
            self.__write_array(strm, f)
        # Not an array
        else:
            f(strm, self.value)

    def __write_non_prim(self, strm: StreamBase):
        """Write non-primitve member to stream"""

        # String type
        if self.type in ("cstr", "str", "wcstr", "wstr"):
            self.__write_string(strm)
        # Whatever type this is, it isn't supported yet
        else:
            raise NotImplementedError(
                "Non-primitive, non-string types not yet supported")

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
        """Write member as array, using the specified write function"""
        assert self.is_array(), "Member is not an array"

        # Variable length array
        if self.is_vl_array():
            for elem in self.value:
                f(strm, elem, *argv)
        # Array of explicit length
        else:
            for i in range(self.length):
                f(strm, self.value[i], *argv)
