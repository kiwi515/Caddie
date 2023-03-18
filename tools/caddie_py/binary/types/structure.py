from caddie_py.binary.types.member import Member
from caddie_py.stream.stream_base import StreamBase
from copy import deepcopy


class Structure(Member):
    """Structure containing members"""

    def __init__(self, name: str, arr: str = None, values: dict = None):
        super().__init__(self.__class__.__name__, name, arr)

        # Convert member list into dictionary
        members = {m.name: m for m in deepcopy(self.MEMBERS)}

        # User initialization
        if values != None:
            for item in values.items():
                k, v = item[0], item[1]
                if k in members:
                    members[k].set_value(v)

        if self.is_array():
            # Cannot initialize variable length array
            if self.is_vl_array():
                self.set_value(list())
            else:
                # In an array, all indices will be initialized the same way
                self.set_value([members] * self.array_size())
        # Single element
        else:
            self.set_value(members)

    def __getitem__(self, key):
        """Access member of structure"""
        return self.value[key]

    def __repr__(self):
        """Convert object to string (for debugging)"""
        return f"{self.type} {self.name} = {{{','.join(self.value)}}}"

    def byte_size(self):
        """Size of structure in bytes"""
        # Size of one instance
        size = sum(m.byte_size() for m in self.MEMBERS)
        # Scale for array
        return size * self.array_size()

    def write(self, strm: StreamBase):
        """Write structure to stream"""
        for dic in self.value:
            for m in dic.values():
                m.write(strm)

    def append(self, member: Member):
        """Append to structure's array"""
        assert self.is_array(), "Not an array!"
        self.value.append(member.value)

    def offset_of(self, key: str):
        """Offset of member in structure"""
        # First set of members
        member_dict = self.value if not self.is_array(
        ) else self.value[0]

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
