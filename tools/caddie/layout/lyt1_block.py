from ..binary import BinaryBlock
from ..stream import OutputStream
from ..types import Vector2f


class LYT1Block(BinaryBlock):
    """Layout block"""

    SIGNATURE = "lyt1"
    DEFAULT_WIDTH = 640.0
    DEFAULT_HEIGHT = 480.0

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        # Extract from JSON
        self.centered = res.get("centered", False)
        self.size = Vector2f.from_list(
            res.get("size", [self.DEFAULT_WIDTH, self.DEFAULT_HEIGHT]))

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += 1  # bool centered
        bsize += 3  # u8 padding[3]
        bsize += 8  # Vector2f size

        return bsize

    def write(self, strm: OutputStream):
        """Serialize block contents to stream"""
        super.write(self, strm)

        # Centered
        strm.write_u8(self.centered)
        # Padding
        self.write_padding(3)
        # Layout size
        self.size.write(strm)

        # Align block to 32B
        self.write_align(strm)
