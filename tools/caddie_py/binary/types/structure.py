from caddie_py.binary.types.member import Member
from caddie_py.stream.stream_base import StreamBase
from caddie_py.utility.util import Util


class Structure(Member):
    """Structure containing members"""

    def __init__(self, _type: str, name: str, arr: str = None, members: list[Member] = []):
        super().__init__(_type, name, arr)
        self._members = dict()

        # Array
        if self.is_array():
            # Explicit array length
            if not self.is_vl_array():
                self.__init_members_array(members)
            else:
                self._members = []
        # Single element
        else:
            self.__init_members_single(members)

    def __getitem__(self, key):
        """Access member of structure"""
        # Array access, return member dict
        if self.is_array():
            key = int(key)
            return self._members[key]
        # No array, direct member access
        else:
            assert key in self._members, f"Member does not exist: {key}"
            return self._members[key]

    def __repr__(self):
        """Convert object to string (for debugging)"""
        text = f"struct {self.type} {{"
        text += "".join(self._members)
        text += "};"
        return text

    def arr_length(self):
        """Structure array length"""
        if self.is_array():
            return len(self._members)
        return 1

    def byte_size(self):
        """Size of structure in bytes"""
        # Size of one instance
        size = sum(m.byte_size() for m in self._get_members())
        # Scale for array
        return size * self.arr_length()

    def offset_of(self, key: str):
        """Offset of member in structure"""
        # First set of members
        member_dict = self._members if not self.is_array(
        ) else self._members[0]

        # Add up offsets until we hit the desired member
        offset = 0
        for item in member_dict.items():
            # Target member found
            if item[0].name == key:
                return offset
            # Keep going
            offset += item[1].byte_size()

        # Member is not in structure
        return -1

    def write(self, strm: StreamBase):
        """Write structure to stream"""
        for dic in self._members:
            for m in dic.values():
                m.write(strm)

    def __init_members_array(self, members: list[Member]):
        """Construct an array of members"""
        assert self.is_array(), "Not an array"

        self._members = [dict()] * self.length

        for i in range(self.length):
            for j, m in enumerate(members):
                assert m.name not in self._members, f"Duplicate member declaration: {m.name}"
                self._members[i][m.name] = m

    def __init_members_single(self, members: list[Member]):
        """Construct one set of members"""
        assert not self.is_array(), "Not a single element"

        self._members = dict()

        for i, m in enumerate(members):
            assert m.name not in self._members, f"Duplicate member declaration: {m.name}"
            self._members[m.name] = m
