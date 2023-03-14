from ..binary import BinaryBlock
from ..stream import OutputStream
from ..types import Vector2f, Vector3f


class PAN1Block(BinaryBlock):
    """Pane block"""

    SIGNATURE = "pan1"
    MAX_NAME_LEN = 16
    MAX_USERDATA_LEN = 8

    def __init__(self, res):
        super().__init__(self.SIGNATURE)

        self.visible = res.get("visible", False)
        self.influenced_alpha = res.get("influenced_alpha", False)
        self.widescreen = res.get("widescreen", False)
        self.base_position = res.get("base_position", 0)
        self.alpha = res.get("alpha", 0)

        assert "name" in res, "Pane is missing name"
        self.name = res["name"]

        # Pane name limited to 20 char buffer (null-terminated)
        if len(self.name) > self.MAX_NAME_LEN - 1:
            print(
                f"[WARN] Pane name {self.name} is too long. It will be truncated to 15 characters (+1 for null terminator)")

        self.user_data = res.get("user_data", "")
        # Pane userdata limited to 8 char buffer (null-terminated)
        if len(self.user_data) > self.MAX_NAME_LEN - 1:
            print(
                f"[WARN] Pane userdata {self.user_data} is too long. It will be truncated to 7 characters (+1 for null terminator)")

        self.trans = Vector3f.from_list(
            res.get("trans", [0.0, 0.0, 0.0]))
        self.trans = Vector3f.from_list(
            res.get("rotate", [0.0, 0.0, 0.0]))
        self.trans = Vector2f.from_list(
            res.get("scale", [0.0, 0.0]))
        self.trans = Vector2f.from_list(
            res.get("size", [0.0, 0.0]))

    def byte_size(self) -> int:
        """Get size of block in bytes"""
        bsize = 0
        bsize += super.byte_size(self)

        bsize += 1  # u8 flag
        bsize += 1  # u8 base_position
        bsize += 1  # u8 alpha
        bsize += self.MAX_NAME_LEN  # char name[20]
        bsize += self.MAX_USERDATA_LEN  # char user_data[8]
        bsize += 12  # Vector3f trans
        bsize += 12  # Vector3f rotate
        bsize += 8  # Vector2f scale
        bsize += 8  # Vector2f size

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
