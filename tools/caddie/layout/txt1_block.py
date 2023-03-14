from ..stream import OutputStream
from ..types import Color, Vector2f
from pan1_block import PAN1Block


class TXT1Block(PAN1Block):
    """Pane block"""

    SIGNATURE = "txt1"

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        self.material_index = res.get("material_index", 0)
        self.font_index = res.get("font_index", 0)
        self.text_position = res.get("text_position", 0)
        self.text_alignment = res.get("text_alignment", 0)

        self.top_color = Color.from_list(res.get("top_color"), [0, 0, 0, 0])
        self.bottom_color = Color.from_list(
            res.get("bottom_color"), [0, 0, 0, 0])

        self.font_size = Vector2f.from_list(res.get("font_size"), [0.0, 0.0])
        self.char_space = res.get("char_space", 0.0)
        self.line_space = res.get("line_space", 0.0)

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += 2  # u16 text_buf_size
        bsize += 2  # u16 text_str_size
        bsize += 2  # u16 material_index
        bsize += 2  # u16 font_index
        bsize += 1  # u8

        return bsize

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # Flags
        flag = 0
        flag |= (self.visible & 1)
        flag |= ((self.influenced_alpha & 1) << 1)
        flag |= ((self.widescreen & 1) << 2)
        strm.write_u8(flag)

        # Base position
        strm.write_u8(self.base_position)
        # Alpha
        strm.write_u8(self.alpha)
        # Padding
        strm.write_padding(1)

        # Name
        strm.write_string_sz(self.name, self.MAX_NAME_LEN)
        # Userdata
        strm.write_string_sz(self.user_data, self.MAX_USERDATA_LEN)

        # Translation
        self.trans.write(strm)
        # Rotation
        self.rotate.write(strm)
        # Scale
        self.scale.write(strm)
        # Size
        self.size.write(strm)

        # Align block to 32B
        self.write_align(strm)
