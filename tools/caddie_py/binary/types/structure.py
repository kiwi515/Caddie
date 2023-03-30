from caddie_py.binary.types.member import Member
from caddie_py.stream.stream_base import StreamBase
from copy import deepcopy


class Structure(Member):
    """Structure containing members"""

    def __init__(self, name: str, arr: str = None, values: dict = None):
        super().__init__(self.__class__.__name__, name, arr)

        # Convert member list into dictionary
        members = {m.name: m for m in deepcopy(self.MEMBERS)}

        if self.is_array():
            # Cannot initialize variable length array
            if self.is_vl_array():
                self.value = list()
            else:
                # In an array, all indices will be initialized the same way
                self.value = [members] * self.array_size()
        # Single element
        else:
            self.value = members

        # User initialization
        if values != None:
            self.set_value(values)

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
        for inst in self:
            for m in inst.values():
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

    def set_value(self, members):
        """Set structure values (members)"""
        if members == None:
            return

        for item in members.items():
            k, v = item[0], item[1]
            if k in self.value:
                self.value[k].set_value(v)
            else:
                print(
                    f"[WARN] Cannot access undeclared member: {self.__class__.__name__}::{k}. Value will be ignored")
