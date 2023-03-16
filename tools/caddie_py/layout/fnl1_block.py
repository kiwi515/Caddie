from caddie_py.binary.block.block_base import BlockBase
from caddie_py.binary.types.structure import Structure
from caddie_py.binary.types.member import Member


class FontDesc(Structure):
    """Font descriptor structure"""

    @staticmethod
    def _get_members() -> list[Member]:
        """Structure members"""
        return [
            Member("u32", "offset"),
            Member("u32", "padding0")
        ]

    def __init__(self, name: str, arr: str = None):
        super().__init__(f"FontDesc", name, arr, self._get_members())

    def append(self, offset: int):
        """Append new font descriptor entry"""
        assert self.is_array(), "Cannot append to non-array member"
        member_dict = {member.name: member for member in self._get_members()}
        member_dict["offset"].set_value(offset)
        self._members.append(member_dict)


class FNL1Block(BlockBase):
    """Font name list block"""

    SIGNATURE = "fnl1"

    def __init__(self, fonts: list[str] = []):
        super().__init__(self.SIGNATURE)
        self.pool_size = 0

        self.add_member(Member("u16", "numEntries", value=len(fonts)))
        self.add_member(Member("u16", "padding0"))
        self.add_member(FontDesc("fontDescs", arr="[]"))
        self.add_member(Member("cstr", "fontNames", arr="[]"))

        # Add fonts to pool
        for f in fonts:
            self.add_font(f)

    def add_font(self, font: str):
        """Add font to name list"""
        # Correct existing offsets (as the string pool will now be shifted)
        for i in range(self["fontDescs"].arr_length()):
            desc = self["fontDescs"][i]
            desc["offset"].value += FontDesc("dummy").byte_size()

        # Add font name to pool
        self["fontNames"].value.append(font)

        # Add new font descriptor
        font_offset = self.pool_size + self.offset_of("fontNames")
        self["fontDescs"].append(font_offset)

        # Increase font count
        self["numEntries"].value += 1
        self.pool_size += len(font) + 1
