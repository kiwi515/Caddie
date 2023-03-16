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
