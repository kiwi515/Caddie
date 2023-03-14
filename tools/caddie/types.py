from .stream import OutputStream


class Vector2f:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    @classmethod
    def from_list(xy: list[float]):
        assert len(xy) == 2, "Invalid initializer list"
        return Vector2f(xy[0], xy[1])

    def write(self, strm: OutputStream):
        strm.write_float(self.x)
        strm.write_float(self.y)


class Vector3f:
    def __init__(self, x: float, y: float, z: float):
        self.x = x
        self.y = y
        self.z = z

    @classmethod
    def from_list(xyz: list[float]):
        assert len(xyz) == 3, "Invalid initializer list"
        return Vector3f(xyz[0], xyz[1], xyz[2])

    def write(self, strm: OutputStream):
        strm.write_float(self.x)
        strm.write_float(self.y)
        strm.write_float(self.z)


class Color:
    def __init__(self, r: int, g: int, b: int, a: int):
        self.r = r
        self.g = g
        self.b = b
        self.a = a

    @classmethod
    def from_list(rgba: list):
        assert len(rgba) == 4, "Invalid initializer list"
        return Color(int(rgba[0]), int(rgba[1]), int(rgba[2]), int(rgba[3]))

    def write(self, strm: OutputStream):
        strm.write_u8(self.r)
        strm.write_u8(self.g)
        strm.write_u8(self.b)
        strm.write_u8(self.a)


class ColorS10(Color):
    def __init__(self, r: int, g: int, b: int, a: int):
        super.__init__(r, g, b, a)

    @classmethod
    def from_list(rgba: list):
        return super.from_list(rgba)

    def write(self, strm: OutputStream):
        strm.write_s16(self.r)
        strm.write_s16(self.g)
        strm.write_s16(self.b)
        strm.write_s16(self.a)
