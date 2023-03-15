from ..stream.ostream import OutputStream
from ..types import Color, Vector2f
from pan1_block import PAN1Block


class TXT1Block(PAN1Block):
    """Pane block"""

    SIGNATURE = "txt1"

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        self.string = ""

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
        bsize += 1  # u8 text_position
        bsize += 1  # u8 text_alignment
        bsize += 4  # GXColor top_color
        bsize += 4  # GXColor bottom_color
        bsize += 4 * 2  # Size font_size
        bsize += 4  # f32 char_space
        bsize += 4  # f32 line_space

        return bsize

    def write(self, strm: OutputStream):
        """Write block buffer to stream"""
        super.write(self, strm)

        # Text buffer size
        strm.write_u16(len(self.string) + 1)
        # Text string size
        strm.write_u16(len(self.string) + 1)

        # Material index
        strm.write_u16(self.material_index)
        # Font index
        strm.write_u16(self.font_index)

        # Text position
        strm.write_u8(self.text_position)
        # Text alignment
        strm.write_u8(self.text_alignment)

        # Top color
        self.top_color.write(strm)
        # Bottom color
        self.bottom_color.write(strm)

        # Font size
        self.font_size.write(strm)

        # Char space
        strm.write_float(self.char_space)
        # Line space
        strm.write_float(self.line_space)

        # Align block to 32B
        self.write_align(strm)
